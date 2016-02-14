#!/usr/bin/make -f

SHELL = /bin/sh

################################################################################
### Solution makefile
################################################################################
ifndef MAIN_MAKE_INCLUDED
    MAIN_MAKE_INCLUDED := 1

    # Macros
    toslnpath   = $(patsubst $(SolutionDir)%,%,$(patsubst $(ProjectDir)%,$(RelativeProjectDir)%,$1))
    toabspath   = $(if $(filter /%,$1),$1,$(ProjectDir)$1)
    fixslnpath  = $(if $(filter $(SolutionDir),$1/),.,$1)
    cleanpath   = $(call fixslnpath,$(call toslnpath,$(abspath $(call toabspath,$1))))
    projnames   = $(foreach Project,$1,$(if $(filter ./,$(Project)),$(SolutionName),$(Project)))

    # Set solution variables
    SolutionDir         := $(shell pwd)/
    SolutionName        := $(notdir $(SolutionDir:%/=%))
    SolutionVersion     := $(shell date +%y.%m.%d)

    # Find projects
    ProjectMakefiles    := $(shell find -maxdepth 2 -name '*.mkproj')
    Projects            := $(patsubst ./%/,%,$(dir $(ProjectMakefiles)))
    ProjectNames        := $(call projnames,$(Projects))

    DistFiles           := Makefile $(patsubst ./%,%,$(ProjectMakefiles))

    # Rules
    .PHONY: all
    all: | build

    .SUFFIXES:
    .SUFFIXES: .c .o

    define IncludeProject
        # Set project variables
        ifeq ($1,./)
            # Support for a project at solution level
            ProjectName         := $(SolutionName)
            ProjectDir          := $(SolutionDir)
            RelativeProjectDir  :=
        else
            ProjectName         := $1
            ProjectDir          := $(SolutionDir)$1/
            RelativeProjectDir  := $$(ProjectName)/
        endif

        # Clear variables
        OutputFile              := a.out
        OutputType              := Application
        OutputDirectory         := $$(ProjectDir)bin/
        BuildDirectory          := $$(ProjectDir)obj/
        SourceDirectories       := $$(ProjectDir)
        IncludeDirectories      :=
        LibraryDirectories      :=
        BuildDependencies       :=
        Libraries               :=
        PreprocessorDefinitions :=
        CC                      := cc
        AR                      := ar
        RANLIB                  := ranlib
        CFLAGS                  :=
        CPPFLAGS                :=
        LDFLAGS                 :=
        LDLIBS                  :=
        ARFLAGS                 := rcs
        AuxiliaryFiles          :=
        Version                 := $(SolutionVersion)

        # Load the project variables
        include $$(ProjectDir)$$(ProjectName).mkproj

        ifeq ($$(OutputType),None)
            # Ignore projects without output
            Projects := $$(filter-out $1,$(ProjectNames))
            ProjectNames := $$(filter-out $$(ProjectName),$(ProjectNames))
        else
            # Generate project rules
            include $(SolutionDir)Makefile

            # Rule for building the project
            $$(ProjectName): $$(Target)
        endif

        ifeq ($1,./)
            # If there is a project at solution level, copy its version
            SolutionVersion := $$(Version)
        endif
    endef

    # Generate project rules
    $(foreach Project,$(Projects),$(eval $(call IncludeProject,$(Project))))

    # Set variables that might depend on a project
    Archive := $(SolutionName)-$(SolutionVersion)

    # Rules
    .PHONY: build
    build: $(ProjectNames)

    .PHONY: rebuild
    rebuild: | $(FastClean) build

    .PHONY: dist
    dist:
	    @! test -d $(Archive) || rm $(Archive)
	    @ln -s . $(Archive)
	    @tar -chzf $(Archive).tar.gz $(addprefix $(Archive)/,$(sort $(DistFiles)))
	    @rm $(Archive)

    .PHONY: clean
    clean: | $(Clean)

    .PHONY: distclean
    distclean: | clean
	    @! test -f $(Archive).tar.gz || rm $(Archive).tar.gz

################################################################################
### Project makefile
################################################################################
else
    # Validate arguments
    ifndef OutputFile
        $(warning OutputFile not set)
        OutputFile := a.out
    endif

    ifndef OutputType
        $(warning OutputType not set)
        OutputType := Application
    endif

    ifndef OutputDirectory
        $(warning OutputDirectory not set)
        OutputDirectory := $(ProjectDir)bin/
    endif

    ifndef BuildDirectory
        $(warning BuildDirectory not set)
        BuildDirectory := $(ProjectDir)obj/
    endif

    ifndef SourceDirectories
        $(warning SourceDirectories not set)
        SourceDirectories := $(ProjectDir)
    endif

    ifndef CC
        $(warning CC not set)
        CC := cc
    endif

    ifndef AR
        $(warning AR not set)
        AR := ar
    endif

    ifndef RANLIB
        $(warning RANLIB not set)
        RANLIB := ranlib
    endif

    ifndef ARFLAGS
        $(warning ARFLAGS not set)
        ARFLAGS := rcs
    endif

    # Clean directory names
    OutputDirectory     := $(call cleanpath,$(OutputDirectory))
    BuildDirectory      := $(call cleanpath,$(BuildDirectory))
    SourceDirectories   := $(foreach PATH,$(SourceDirectories),$(call cleanpath,$(PATH)))
    IncludeDirectories  := $(foreach PATH,$(IncludeDirectories),$(call cleanpath,$(PATH)))
    LibraryDirectories  := $(foreach PATH,$(LibraryDirectories),$(call cleanpath,$(PATH)))
    HeaderDirectories   := $(sort $(SourceDirectories) $(filter $(RelativeProjectDir)%,$(IncludeDirectories)))

    # Find files
    SourceFiles         := $(foreach PATH,$(SourceDirectories),$(patsubst ./%,%,$(shell ! test -d $(PATH) || find $(PATH) -name '*.c')))
    HeaderFiles         := $(foreach PATH,$(HeaderDirectories),$(patsubst ./%,%,$(shell ! test -d $(PATH) || find $(PATH) -name '*.h')))
    AuxiliaryFiles      := $(foreach FILE,$(AuxiliaryFiles),$(shell find $(RelativeProjectDir) -name '$(FILE)'))
    ObjectFiles         := $(foreach PATH,$(SourceDirectories),$(patsubst $(RelativeProjectDir)%.c,$(BuildDirectory)/%.o,$(SourceFiles)))
    DependencyFiles     := $(foreach PATH,$(SourceDirectories),$(patsubst $(RelativeProjectDir)%.c,$(BuildDirectory)/%.d,$(SourceFiles)))

    # Find all intermediate directories
    BuildDirectories    := $(patsubst ./%,%,$(sort $(foreach FILE,$(ObjectFiles),$(dir $(FILE)))))

    # Set compiler and linker options
    CPPFLAGS    += $(addprefix -I,$(IncludeDirectories))
    LDFLAGS     += $(addprefix -L,$(LibraryDirectories))
    CPPFLAGS    += $(addprefix -D,$(PreprocessorDefinitions))
    LDLIBS      += $(addprefix -l,$(Libraries))

    ifeq ($(OutputType),SharedLibrary)
        CFLAGS  += -fPIC
    endif

    # Determine compile method based on the OutputType
    ifeq ($(OutputType),Application)
        link = $(CC) $(CPPFLAGS) $(CFLAGS) -o $1 $2 $(LDFLAGS) $(LDLIBS)
    else ifeq ($(OutputType),SharedLibrary)
        link = $(CC) $(CPPFLAGS) $(CFLAGS) -shared -o $1 $2 $(LDFLAGS) $(LDLIBS)
    else ifeq ($(OutputType),StaticLibrary)
        link = $(AR) $(ARFLAGS) $1 $2 && $(RANLIB) $1
    else
        $(error Invalid OutputType. Must be one of: Application, SharedLibrary, StaticLibrary)
    endif

    # Determine target
    Target := $(OutputDirectory)/$(OutputFile)

    # Generates rules for the project
    define GenerateRules
        $(Target): $(ObjectFiles) $(BuildDependencies) | $(OutputDirectory)
	        @echo "Linking $(ProjectName)"
	        @$(call link,$(Target),$(ObjectFiles))

        $(BuildDirectory)/%.o: $(RelativeProjectDir)%.c $(SolutionDir)Makefile $(ProjectDir)$(ProjectName).mkproj | $(BuildDirectories)
	        @echo "Compiling $$<"
	        @$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $$@ $$<
	        @$(CC) $(CPPFLAGS) $(CFLAGS) -MM -MP $$< | \
		        sed -e '0,/.*:/{s|.*:|$$@:|}' > $(BuildDirectory)/$$*.d

        .PHONY: rebuild_$(ProjectName)
        rebuild_$(ProjectName): | .fastclean_$(ProjectName) $(ProjectName)

        .PHONY: clean_$(ProjectName)
        clean_$(ProjectName): | .fastclean_$(ProjectName)
	        @! test -d $(OutputDirectory) || find $(OutputDirectory) -maxdepth 1 -type d -empty -delete
	        @! test -d $(BuildDirectory) || find $(BuildDirectory) -type d -empty -delete

        .PHONY: .fastclean_$(ProjectName)
        .fastclean_$(ProjectName):
	        @rm -f $(Target) $(ObjectFiles) $(DependencyFiles)

        $(OutputDirectory) $(BuildDirectories) : ; @mkdir -p $$@

        # Record project-specific targets
        FastClean   += .fastclean_$(ProjectName)
        Clean       += clean_$(ProjectName)
        DistFiles   += $(SourceFiles) $(HeaderFiles) $(AuxiliaryFiles)
    endef

    # Generate the rules
    $(eval $(call GenerateRules))

    # Include dependency rules
    -include $(DependencyFiles)
endif
