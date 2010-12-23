# START SNIPPET: Content
# If the CECILIA_ROOT variable is defined, look for 'ceciliac' in this directory
# otherwise, expect that 'ceciliac' is in the PATH.
ifdef CECILIA_ROOT
  # If CECILIA_ROOT contains '\', replace them by '/' (for Windows)
  CECILIAC = $(subst \,/, $(CECILIA_ROOT)/bin/ceciliac)
else 
  CECILIAC = ceciliac
endif

all: graphiCALL 

# START SNIPPET: graphiCALL-rule
graphiCALL: build/graphiCALL
	$(CECILIAC) -src-path=src -o=build/graphiCALL -t=unix \
	  graphiCALL.graphiCALL:graphiCALL
# END SNIPPET: graphiCALL-rule

build/graphiCALL:
	mkdir -p build/graphiCALL

clean:
	rm -Rf build target

run: graphiCALL
	./build/graphiCALL/obj/graphiCALL

.PHONY: all graphiCALL
	
.SILENT: clean
