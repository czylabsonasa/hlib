SUBDIRS = $(shell find . -type d -name "app*" -printf "%f " )

.PHONY: $(SUBDIRS) build clean

$(SUBDIRS):
	$(MAKE) -C $@

build: $(SUBDIRS)
	
	
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
		echo "";\
   done


