SUBDIRS = $(shell find . -type d -name "app*" -printf "%f " )

.PHONY: build depend clean


build:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir app; \
		echo "";\
   done

depend:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir depend; \
		echo "";\
   done


clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
		echo "";\
   done
