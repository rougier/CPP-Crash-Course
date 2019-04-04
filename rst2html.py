#!/usr/bin/python
# coding: utf-8

# :Author: Georg Brandl; Felix Wiemann; Günter Milde
# :Date: $Date: 2011-08-27 00:23:29 +0200 (Sam, 27. Aug 2011) $
# :Copyright: This module has been placed in the public domain.
#
# This is a merge of `Using Pygments in ReST documents`_ from the pygments_
# documentation, and a `proof of concept`_ by Felix Wiemann.
#
# .. class:: borderless
#
# ========== =============================================================
# 2007-06-01 Removed redundancy from class values.
# 2007-06-04 Merge of successive tokens of same type
#            (code taken from pygments.formatters.others).
# 2007-06-05 Separate docutils formatter script
#            Use pygments' CSS class names (like the html formatter)
#            allowing the use of pygments-produced style sheets.
# 2007-06-07 Merge in the formatting of the parsed tokens
#            (misnamed as docutils_formatter) as class DocutilsInterface
# 2007-06-08 Failsave implementation (fallback to a standard literal block
#            if pygments not found)
# 2010-11-27 Rename directive from "code-block" to "code".
#            Fix fallback if pygments not found.
#            Use class-based interface.
#            Add "number-lines" option.
# ========== =============================================================
#
# ::

"""Define and register a code directive using pygments"""

# Requirements
# ------------
# ::

from docutils import nodes
from docutils.parsers.rst import directives, Directive
from docutils.parsers.rst.roles import set_classes
try:
    import pygments
    from pygments.lexers import get_lexer_by_name
    from pygments.formatters.html import _get_ttype_class
    with_pygments = True
except ImportError:
    with_pygments = False

# Customisation
# -------------
#
# Do not insert inline nodes for the following tokens.
# (You could add e.g. Token.Punctuation like ``['', 'p']``.) ::

unstyled_tokens = [''] # Token.Text

# Lexer
# ---------
#
# This interface class combines code from
# pygments.formatters.html and pygments.formatters.others.

class Lexer(object):
    """Parse `code` lines and yield "classified" tokens.

    Arguments

      code     -- list of source code lines to parse
      language -- formal language the code is written in.

    Merge subsequent tokens of the same token-type.

    Iterating over an instance yields the tokens as ``(ttype_class, value)``
    tuples, where `ttype_class` is taken from pygments.token.STANDARD_TYPES
    and corresponds to the class argument used in pygments html output.
    """

    def __init__(self, code, language):
        """
        Set up a lexical analyzer for `code` in `language`.
        """
        self.code = code
        self.language = language
        self.lexer = None
        # get lexical analyzer for `language`:
        if language in ('', 'text'):
            return
        if not with_pygments:
            raise ApplicationError('Cannot highlight code. '
                                    'Pygments package not found.')
        try:
            self.lexer = get_lexer_by_name(self.language)
        except pygments.util.ClassNotFound:
            raise ApplicationError('Cannot highlight code. '
                'No Pygments lexer found for "%s".' % language)

    # Since version 1.2. (released Jan 01, 2010) Pygments has a 
    # TokenMergeFilter. ``self.merge(tokens)`` in __iter__ can be 
    # replaced by ``self.lexer.add_filter('tokenmerge')`` in __init__.

    def merge(self, tokens):
        """Merge subsequent tokens of same token-type.

        Also strip the final '\n' (added by pygments).
        """
        tokens = iter(tokens)
        (lasttype, lastval) = tokens.next()
        for ttype, value in tokens:
            if ttype is lasttype:
                lastval += value
            else:
                yield(lasttype, lastval)
                (lasttype, lastval) = (ttype, value)
        if lastval != '\n':
            yield(lasttype, lastval)

    def __iter__(self):
        """Parse self.code and yield "classified" tokens
        """
        codestring = u'\n'.join(self.code)
        if self.lexer is None:
            yield [('', codestring)]
            return
        tokens = pygments.lex(codestring, self.lexer)
        for ttype, value in self.merge(tokens):
            # yield (ttype, value)  # token type objects
            yield (_get_ttype_class(ttype), value) # short name strings


class NumberLines(object):
    """Insert linenumber-tokens in front of every newline.
    
    Arguments
    
       tokens    -- iterable of ``(ttype_class, value)`` tuples
       startline -- first line number
       endline   -- last line number

    Iterating over an instance yields the tokens preceded by
    a ``('ln', '<line number>')`` token for every line.
    Multi-line tokens from pygments are splitted. """

    def __init__(self, tokens, startline, endline):
        self.tokens = tokens
        self.startline = startline
        # pad linenumbers, e.g. endline == 100 -> fmt_str = '%3d '
        self.fmt_str = '%%%dd ' % len(str(endline))

    def __iter__(self):
        lineno = self.startline
        yield ('ln', self.fmt_str % lineno)
        for ttype, value in self.tokens:
            lines = value.split('\n')
            for line in lines[:-1]:
                yield (ttype, line + '\n')
                lineno += 1
                yield ('ln', self.fmt_str % lineno)
            yield (ttype, lines[-1])


# CodeBlock directive
# --------------------
# ::

class CodeBlock(Directive):
    """Parse and mark up content of a code block.
    """
    optional_arguments = 1
    option_spec = {'class': directives.class_option,
                   'name': directives.unchanged,
                   'number-lines': directives.unchanged # integer or None
                  }
    has_content = True

    def run(self):
        self.assert_has_content()
        if self.arguments:
            language = self.arguments[0]
        else:
            language = ''
        set_classes(self.options)
        classes = ['code', language]
        if 'classes' in self.options:
            classes.extend(self.options['classes'])
            
        # TODO: config setting to skip lexical analysis: 
        ## if document.settings.no_highlight:
        ##      language = ''

        # set up lexical analyzer
        tokens = Lexer(self.content, language)

        if 'number-lines' in self.options:
            # optional argument `startline`, defaults to 1
            try: 
                startline = int(self.options['number-lines'] or 1)
            except ValueError:
                raise self.error(':number-lines: with non-integer start value')
            endline = startline + len(self.content)
            # add linenumber filter:
            tokens = NumberLines(tokens, startline, endline)

        node = nodes.literal_block('\n'.join(self.content), classes=classes)
        self.add_name(node)
        
        # analyze content and add nodes for every token
        for cls, value in tokens:
            # print (cls, value)
            if cls in unstyled_tokens:
                # insert as Text to decrease the verbosity of the output.
                node += nodes.Text(value, value)
            else:
                node += nodes.inline(value, value, classes=[cls])

        return [node]


# Register Directive
# ------------------
# ::

directives.register_directive('code', CodeBlock)

# .. _doctutils: http://docutils.sf.net/
# .. _pygments: http://pygments.org/
# .. _Using Pygments in ReST documents: http://pygments.org/docs/rstdirective/
# .. _proof of concept:
#      http://article.gmane.org/gmane.text.docutils.user/3689
#
# Test output
# -----------
#
# If called from the command line, call the docutils publisher to render the
# input::

if __name__ == '__main__':
    from docutils.core import publish_cmdline, default_description
    description = 'code-block directive test output' + default_description
    try:
        import locale
        locale.setlocale(locale.LC_ALL, '')
    except:
        pass
    # Uncomment the desired output format:
    # publish_cmdline(writer_name='pseudoxml', description=description)
    # publish_cmdline(writer_name='xml', description=description)
    publish_cmdline(writer_name='html', description=description)
    # publish_cmdline(writer_name='latex', description=description)
