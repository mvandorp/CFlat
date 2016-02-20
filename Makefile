#!/usr/bin/make -f

SHELL = /bin/sh

################################################################################
### Add rebuild as an alias for --always-make build
################################################################################
ifneq (,$(filter rebuild,$(MAKECMDGOALS)))
    .PHONY: rebuild
    rebuild:
		@$(MAKE) --no-print-directory --always-make build $(filter-out rebuild,$(MAKECMDGOALS))

################################################################################
### Solution makefile
################################################################################
else ifndef MODE
    # Color constants
    COLOR_DEFAULT   := \033[0m
    COLOR_RED       := \033[1;31m
    COLOR_GREEN     := \033[1;32m
    COLOR_YELLOW    := \033[1;33m
    COLOR_BLUE      := \033[1;34m
    COLOR_PURPLE    := \033[1;35m
    COLOR_CYAN      := \033[1;36m
    COLOR_WHITE     := \033[1;37m

    # String constants
    AWK_FORMAT      = awk '{ printf "$(COLOR_WHITE)>$(COLOR_DEFAULT) %20s", $$1; }'
    OK_STRING       := $(shell echo "$(COLOR_GREEN)[OK]$(COLOR_DEFAULT)" | $(AWK_FORMAT); )
    ERROR_STRING    := $(shell echo "$(COLOR_RED)[ERROR]$(COLOR_DEFAULT)" | $(AWK_FORMAT); )
    WARN_STRING     := $(shell echo "$(COLOR_YELLOW)[WARNING]$(COLOR_DEFAULT)" | $(AWK_FORMAT); )

    # Print functions
    config_warning  = $(info $(shell echo               \
        "$(COLOR_RED)[CONFIG WARNING]$(COLOR_DEFAULT)"  \
        "$(COLOR_WHITE)$(ProjectName)$(COLOR_DEFAULT): $1"; ))
    build_ok        = $(info $(shell echo "$(OK_STRING) $1"; ))
    build_warning   = $(info $(shell echo "$(WARN_STRING) $1"; ))
    build_error     = $(info $(shell echo "$(ERROR_STRING) $1"; ))

    # Functions
    toslnpath       = $(patsubst $(SolutionDir)%,%,$(patsubst $(ProjectDir)%,$(RelativeProjectDir)%,$1))
    toabspath       = $(if $(filter /%,$1),$1,$(ProjectDir)$1)
    fixslnpath      = $(if $(filter $(SolutionDir),$1/),.,$1)
    cleanpath       = $(call fixslnpath,$(call toslnpath,$(abspath $(call toabspath,$1))))
    find            = $(shell find $(dir $1) -name $(notdir $1))
    vcxproj_headers = $(shell sed -n 's/\s*<ClInclude\s\+Include\s*=\s*\"\(.*\)\"\s*\/>\s*/\1/p' $(call cleanpath,$1) \
        | sed 's/\\/\//g')
    vcxproj_sources = $(shell sed -n 's/\s*<ClCompile\s\+Include\s*=\s*\"\(.*\)\"\s*\/>\s*/\1/p' $(call cleanpath,$1) \
        | sed 's/\\/\//g')
    ifzero          = $(if $(filter 0,$1),$2,$3)

    # Shell macros
    COMPILE = $(.CC) $(.CPPFLAGS) $(.CFLAGS) -c -o $@ $<
    GENERATE_DEPENDENCIES = \
        $(.CC) $(.CPPFLAGS) $(.CFLAGS) -MM -MP $< | sed -e '0,/.*:/{s|.*:|$@:|}' > $(.BuildDirectory)/$*.d

    # Build statistics
    evalnum         = $(shell echo "$$(($1))"; )
    ActiveCounter   := 0
    BuiltCounter    := 0
    FailedCounter   := 0
    ActiveCount     = $(call evalnum,$(ActiveCounter))
    BuiltCount      = $(call evalnum,$(BuiltCounter))
    FailedCount     = $(call evalnum,$(FailedCounter))
    UpToDateCount   = $(call evalnum,$(ActiveCount) - $(BuiltCount) - $(FailedCount))
    SkippedCount    = $(call evalnum,$(words $(ProjectNames)) - $(ActiveCount))
    BuildReport     =                                                                                               \
        "$(COLOR_WHITE)=========$(COLOR_DEFAULT) Build:                                                             \
        $(call ifzero,$(BuiltCount),$(COLOR_DEFAULT),$(COLOR_GREEN))$(BuiltCount) succeeded$(COLOR_DEFAULT),        \
        $(call ifzero,$(FailedCount),$(COLOR_DEFAULT),$(COLOR_RED))$(FailedCount) failed$(COLOR_DEFAULT),           \
        $(call ifzero,$(UpToDateCount),$(COLOR_DEFAULT),$(COLOR_GREEN))$(UpToDateCount) up-to-date$(COLOR_DEFAULT), \
        $(call ifzero,$(SkippedCount),$(COLOR_DEFAULT),$(COLOR_YELLOW))$(SkippedCount) skipped$(COLOR_DEFAULT)      \
        $(COLOR_WHITE)=========$(COLOR_DEFAULT)"

    # Initialize solution variables
    SolutionDir         := $(shell pwd)/
    SolutionName        := $(notdir $(SolutionDir:%/=%))
    SolutionVersion     := $(shell date +%Y.%m.%d)
    DistName             = $(SolutionName)-$(SolutionVersion)

    # Find projects
    ProjectMakefiles    := $(shell find -maxdepth 2 -name '*.mkproj')
    ProjectNames        := $(patsubst ./%/,%,$(dir $(ProjectMakefiles)))
    Projects            :=

    # Set initial files to be included with a distribution
    DistFiles           := Makefile $(patsubst ./%,%,$(ProjectMakefiles))

    # Initialize prerequisite lists
    DistClean           :=
    Clean               :=
    FastClean           :=
    HtmlDoc             :=

    define LoadProject
        # Set project variables
        ifeq ($2,./)
            ProjectName         := $(SolutionName)
            ProjectDir          := $(SolutionDir)
            RelativeProjectDir  :=
        else
            ProjectName         := $2
            ProjectDir          := $(SolutionDir)$2/
            RelativeProjectDir  := $$(ProjectName)/
        endif

        # Clear project variables
        OutputFile              := a.out
        OutputType              := Application
        OutputDirectory         := $$(ProjectDir)bin/
        BuildDirectory          := $$(ProjectDir)obj/
        SourceFiles             :=
        HeaderFiles             :=
        IncludeDirectories      :=
        LibraryDirectories      :=
        ProjectDependencies     :=
        Libraries               :=
        PreprocessorDefinitions :=
        AR                      := ar
        ARFLAGS                 := rcs
        CC                      := cc
        CFLAGS                  :=
        CPPFLAGS                :=
        LDFLAGS                 :=
        LDLIBS                  :=
        Doxyfile                :=
        AuxDistributionFiles    :=
        Version                 := $(SolutionVersion)

        # Recursively include this makefile with the set mode
        MODE := $1
        include $(SolutionDir)Makefile

        ifeq ($1,LOAD_PROJECT)
            # Add project targets and files
            DistFiles += $$(AuxDistributionFiles) $$(Doxyfile)
            DistClean += distclean_$$(ProjectName)

            ifneq (,$$(GeneratesHtmlDoc))
                HtmlDoc += html_$$(ProjectName)
            endif

            ifneq ($$(OutputType),None)
                DistFiles += $$(SourceFiles) $$(HeaderFiles)
                Clean += clean_$$(ProjectName)
                FastClean += .fastclean_$$(ProjectName)
                Projects += $$(ProjectName)
            endif

            # If the project is at solution level, copy its version
            ifeq ($2,./)
                SolutionVersion := $$(Version)
            endif
        endif
    endef

    # Rules
    .PHONY: all
    all: | build

    # Generate project rules
    $(foreach Project,$(ProjectNames),$(eval $(call LoadProject,FIND_TARGET,$(Project))))
    $(foreach Project,$(ProjectNames),$(eval $(call LoadProject,LOAD_PROJECT,$(Project))))

    .PHONY: build
    build: $(Projects)
		@echo $(BuildReport)

    .PHONY: rebuild
    rebuild: | build

    .PHONY: doc
    doc: | html

    .PHONY: html
    html: | .doxygen $(HtmlDoc)

    .PHONY: .doxygen
    .doxygen:
		@command -v doxygen >/dev/null 2>&1 || {                                                            \
			echo                                                                                            \
				"$(COLOR_RED)[ERROR]$(COLOR_DEFAULT):"                                                      \
				"The program 'doxygen' is needed to generate html documentation but"                        \
				"is currently not installed. You can install it by typing: sudo apt-get install doxygen";   \
			exit 1;                                                                                         \
		}

    .PHONY: dist
    dist: | tar

    .PHONY: tar
    tar:
		@rm -f $(DistName)
		@ln -s . $(DistName)
		@tar -chzf $(DistName).tar.gz $(addprefix $(DistName)/,$(sort $(DistFiles)))
		@rm -f $(DistName)

    .PHONY: clean
    clean: | $(Clean)

    .PHONY: distclean
    distclean: | $(DistClean) clean
		@rm -f $(DistName).tar.gz

################################################################################
### Project makefile
################################################################################
else ifeq ($(MODE),LOAD_PROJECT)
    include $(ProjectDir)$(ProjectName).mkproj

    # Initialize local variables
    GeneratesHtmlDoc        :=
    VcxProj                 := $(ProjectDir)$(ProjectName).vcxproj

    # Clean directory names
    OutputDirectory         := $(call cleanpath,$(OutputDirectory))
    BuildDirectory          := $(call cleanpath,$(BuildDirectory))
    IncludeDirectories      := $(foreach PATH,$(IncludeDirectories),$(call cleanpath,$(PATH)))
    LibraryDirectories      := $(foreach PATH,$(LibraryDirectories),$(call cleanpath,$(PATH)))

    # Fix paths of auxiliary distribution files
    AuxDistributionFiles    := \
        $(foreach FILE,$(AuxDistributionFiles),$(patsubst ./%,%,$(call find,$(call cleanpath,$(FILE)))))

    # Allow source files to be inherited from .vcxproj
    ifeq ($(SourceFiles),VCXPROJ_SOURCES)
        ifeq (,$(shell test -f $(VcxProj)))
            SourceFiles := $(call vcxproj_sources,$(VcxProj))
        else
            $(call config_warning,SourceFiles set to VCXPROJ_SOURCES but a VC++ Project could not be found)
            SourceFiles :=
        endif
    endif

    # Allow header files to be inherited from .vcxproj
    ifeq ($(HeaderFiles),VCXPROJ_HEADERS)
        ifeq (,$(shell test -f $(VcxProj)))
            HeaderFiles := $(call vcxproj_headers,$(VcxProj))
        else
            $(call config_warning,HeaderFiles set to VCXPROJ_HEADERS but a VC++ Project could not be found)
            HeaderFiles :=
        endif
    endif

    # Find files
    SourceFiles         := $(foreach FILE,$(SourceFiles),$(call cleanpath,$(FILE)))
    HeaderFiles         := $(foreach FILE,$(HeaderFiles),$(call cleanpath,$(FILE)))

    #---------------------------------------------------------------------------
    # Doxygen HTML documentation
    #---------------------------------------------------------------------------
    ifdef Doxyfile

        # Fix path of doxyfile
        Doxyfile := $(call cleanpath,$(Doxyfile))

        # Load doxyfile
        include $(Doxyfile)

        ifeq ($(GENERATE_HTML),YES)
            GeneratesHtmlDoc := 1

            ifndef OUTPUT_DIRECTORY
                $(call config_warning,OUTPUT_DIRECTORY not set for $(Doxyfile))
                OUTPUT_DIRECTORY := ./
            endif

            ifndef HTML_OUTPUT
                $(call config_warning,HTML_OUTPUT not set for $(Doxyfile))
                HTML_OUTPUT := html
            endif

            # Find the output directories
            DocDir := $(call cleanpath,$(OUTPUT_DIRECTORY))

            ifneq (,$(filter /%,$$(HTML_OUTPUT)))
                DocHtmlDir := $(call cleanpath,$(HTML_OUTPUT))
            else
                DocHtmlDir := $(call cleanpath,$(OUTPUT_DIRECTORY)/$(HTML_OUTPUT))
            endif

            # Find all directories that contain source files or header files
            SourceDirectories := $(patsubst %/,%,$(sort $(foreach FILE,$(SourceFiles) $(HeaderFiles),$(dir $(FILE)))))
            ImportantDirectories:= $(ProjectName) $(SourceDirectories) $(IncludeDirectories) $(LibraryDirectories)

            # Expands to nothing if the output directory is an important directory
            SafeDocDir := $(if $(filter $(DocDir)%,$(ImportantDirectories)),,$(DocDir))
            SafeDocHtmlDir := $(if $(filter $(DocHtmlDir)%,$(ImportantDirectories)),,$(DocHtmlDir))

            # Rules
            .PHONY: html_$(ProjectName)
            html_$(ProjectName): .Doxyfile      := $(SolutionDir)$(Doxyfile)
            html_$(ProjectName): .ProjectDir    := $(ProjectDir)
            html_$(ProjectName): .ProjectName   := $(ProjectName)
            html_$(ProjectName):
				@echo                                                                       \
					"$(COLOR_WHITE)=========  Generating documentation:$(COLOR_DEFAULT)"    \
					"Project: $(COLOR_BLUE)$(.ProjectName)$(COLOR_DEFAULT),"                \
					"Type: Html $(COLOR_WHITE)=========$(COLOR_DEFAULT)"
				@cd $(.ProjectDir) && doxygen $(.Doxyfile)

            .PHONY: docclean_$(ProjectName)
            docclean_$(ProjectName): .DocHtmlDir := $(SafeDocHtmlDir)
            docclean_$(ProjectName): .DocDir := $(SafeDocDir)
            docclean_$(ProjectName):
				@$(if $(.DocHtmlDir),! test -d $(.DocHtmlDir) || rm -r $(.DocHtmlDir),)
				@$(if $(.DocDir),! test -d $(.DocDir) || find $(.DocDir) -maxdepth 0 -type d -empty -delete,)
        endif
    endif

    #---------------------------------------------------------------------------
    # C project
    #---------------------------------------------------------------------------
    ifneq ($(OutputType),None)
        ifndef OutputFile
            $(call config_warning,OutputFile not set)
            OutputFile := a.out
        endif

        ifndef OutputType
            $(call config_warning,OutputType not set)
            OutputType := Application
        endif

        ifndef OutputDirectory
            $(call config_warning,OutputDirectory not set)
            OutputDirectory := $(ProjectDir)bin/
        endif

        ifndef BuildDirectory
            $(call config_warning,BuildDirectory not set)
            BuildDirectory := $(ProjectDir)obj/
        endif

        ifndef SourceFiles
            $(call config_warning,No source files specified)
        endif

        ifndef CC
            $(call config_warning,CC not set)
            CC := cc
        endif

        ifndef AR
            $(call config_warning,AR not set)
            AR := ar
        endif

        ifndef ARFLAGS
            $(call config_warning,ARFLAGS not set)
            ARFLAGS := rcs
        endif

        # Find files
        Makefiles           := $(SolutionDir)Makefile $(ProjectDir)$(ProjectName).mkproj
        ObjectFiles         := $(patsubst $(RelativeProjectDir)%.c,$(BuildDirectory)/%.o,$(SourceFiles))
        DependencyFiles     := $(patsubst $(RelativeProjectDir)%.c,$(BuildDirectory)/%.d,$(SourceFiles))

        # Find all build directories so that they can be created
        BuildDirectories    := $(patsubst ./%,%,$(sort $(foreach FILE,$(ObjectFiles),$(dir $(FILE)))))

        # Determine target
        Target              := $(OutputDirectory)/$(OutputFile)

        # Set compiler and linker options
        CPPFLAGS            += $(addprefix -I,$(IncludeDirectories))
        CPPFLAGS            += $(addprefix -D,$(PreprocessorDefinitions))
        LDFLAGS             += $(addprefix -L,$(LibraryDirectories))
        LDLIBS              += $(addprefix -l,$(Libraries))

        ifeq ($(OutputType),SharedLibrary)
            CFLAGS          += -fPIC
        endif

        # Determine link command based on the OutputType
        ifeq ($(OutputType),Application)
            link = $(CC) $(CPPFLAGS) $(CFLAGS) -o $1 $2 $(LDFLAGS) $(LDLIBS)
        else ifeq ($(OutputType),SharedLibrary)
            link = $(CC) $(CPPFLAGS) $(CFLAGS) -shared -o $1 $2 $(LDFLAGS) $(LDLIBS)
        else ifeq ($(OutputType),StaticLibrary)
            link = $(AR) $(ARFLAGS) $1 $2
        else
            $(error Invalid OutputType. Must be one of: None, Application, SharedLibrary, StaticLibrary)
        endif

        # Find all prerequisite binaries for this project
        $(eval PrerequisiteTargets := $(patsubst %,$$(.target_%),$(ProjectDependencies)))

        # Rules
        .PHONY: .prebuild_$(ProjectName)
        .prebuild_$(ProjectName): .ProjectName:=$(ProjectName)
        .prebuild_$(ProjectName):
			$(eval ActiveCounter := $(ActiveCounter)+1)
			@echo "$(COLOR_WHITE)>------ Build started:$(COLOR_DEFAULT)" \
				"Project: $(COLOR_BLUE)$(.ProjectName)$(COLOR_DEFAULT)"

        .PHONY: $(ProjectName)
        $(ProjectName): $(ProjectDependencies) .prebuild_$(ProjectName) $(Target)
			$(eval $(if $(filter $@,$(MAKECMDGOALS)),$$(info $(shell echo $(BuildReport); )),))

        $(Target): .link :=$(call link, $(Target), $(ObjectFiles))
        $(Target): $(ObjectFiles) $(PrerequisiteTargets) $(Makefiles) | $(OutputDirectory)
			$(eval LogFile := $(shell rm -f $@; mktemp))
			$(eval ExitCode := $(shell $(.link) > $(LogFile) 2>&1; echo $$?; ))
			$(eval HasWarnings := $(shell test -s $(LogFile); ))
			$(eval $(call ifzero, $(ExitCode), BuiltCounter := $(BuiltCounter)+1, FailedCounter := $(FailedCounter)+1))
			$(eval $(call ifzero, $(ExitCode),                                      \
				$(call ifzero, $(HasWarnings),                                      \
					$$(call build_warning,$(COLOR_WHITE)Linking$(COLOR_DEFAULT) $@),\
					$$(call build_ok,$(COLOR_WHITE)Linking$(COLOR_DEFAULT) $@)),    \
				$$(call build_error,$(COLOR_WHITE)Linking$(COLOR_DEFAULT) $@)))
			@cat $(LogFile); rm -f $(LogFile)

        $(BuildDirectory)/%.o: .CC              :=$(CC)
        $(BuildDirectory)/%.o: .CFLAGS          :=$(CFLAGS)
        $(BuildDirectory)/%.o: .CPPFLAGS        :=$(CPPFLAGS)
        $(BuildDirectory)/%.o: .BuildDirectory  :=$(BuildDirectory)
        $(BuildDirectory)/%.o: $(RelativeProjectDir)%.c $(Makefiles) | $(BuildDirectories)
			@rm -f $@;                                  \
			LOG=$$($(COMPILE) 2>&1);                    \
			if [ $$? -eq 0 ]; then                      \
				$(GENERATE_DEPENDENCIES);               \
				if [ "$$LOG" = "" ]; then               \
					echo "$(OK_STRING) $<";             \
				else                                    \
					echo "$(WARN_STRING) $<\n$$LOG";    \
				fi;                                     \
			else                                        \
				echo "$(ERROR_STRING) $<\n$$LOG";       \
			fi;

        .PHONY: rebuild_$(ProjectName)
        rebuild_$(ProjectName): | .fastclean_$(ProjectName) $(ProjectName) .postbuild

        .PHONY: clean_$(ProjectName)
        clean_$(ProjectName): .OutputDirectory:=$(OutputDirectory)
        clean_$(ProjectName): .BuildDirectory:=$(BuildDirectory)
        clean_$(ProjectName): | .fastclean_$(ProjectName)
			@! test -d $(.OutputDirectory) || find $(.OutputDirectory) -maxdepth 0 -type d -empty -delete
			@! test -d $(.BuildDirectory) || find $(.BuildDirectory) -type d -empty -delete

        .PHONY: .fastclean_$(ProjectName)
        .fastclean_$(ProjectName): Files:=$(Target) $(ObjectFiles) $(DependencyFiles)
        .fastclean_$(ProjectName):
			@rm -f $(Files)

        $(OutputDirectory) $(BuildDirectories): ; @mkdir -p $@

        # Include dependency rules
        -include $(DependencyFiles)
    endif

    .PHONY: distclean_$(ProjectName)
    distclean_$(ProjectName): | $(if $(GeneratesHtmlDoc),docclean_$(ProjectName),)

################################################################################
### Find the target of a project
################################################################################
else ifeq ($(MODE),FIND_TARGET)
    include $(ProjectDir)$(ProjectName).mkproj

    OutputFile ?= a.out
    OutputDirectory ?= $(ProjectDir)bin/
    OutputDirectory := $(call cleanpath,$(OutputDirectory))

    .target_$(ProjectName) := $(OutputDirectory)/$(OutputFile)

################################################################################
### Invalid mode
################################################################################
else
    $(error Invalid mode: $(MODE))
endif
