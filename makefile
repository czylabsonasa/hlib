SUBDIRS = $(shell find . -maxdepth 1 -type d -name "app*" -printf "%f " )

.PHONY: build depend clean

build:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir app; \
		echo ""; \
   done


# nothing to be done, akkor is ha megcsinalja
depend:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir depend; \
		echo ""; \
   done


clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
		echo ""; \
   done

