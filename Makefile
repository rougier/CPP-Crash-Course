MAKE             = /usr/bin/make
RST2HTML         = ./rst2html.py
STYLESHEET       = stylesheet.css
RST2HTML_OPTIONS = --strip-comments             \
                   --report=3                   \
                   --section-numbering          \
                   --no-toc-backlinks           \
                   --template=page.tmpl         \
                   --cloak-email-addresses      \
                   --stylesheet=$(STYLESHEET)   \
                   --link-stylesheet

SOURCES = $(wildcard *.rst)
OBJECTS = $(subst .rst,.html, $(SOURCES))

all: $(OBJECTS) pygment.css

#pygment.css: 
#	@pygmentize -S tango -f html > pygment.css

%.html: %.rst Makefile
	@echo "  - $@"
	@$(RST2HTML) $(RST2HTML_OPTIONS) $< $@

clean:
	@-rm -f $(OBJECTS)

distclean: clean
	@-rm -f `find . -name "*~"`

.PHONY: all home clean distclean
