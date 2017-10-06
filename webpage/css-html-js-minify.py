#!/usr/bin/python3
# -*- coding: utf-8 -*-


"""CSS-HTML-JS-Minify.

StandAlone Async single-file cross-platform no-dependency Minifier for the Web.
"""


import gzip
import itertools
import logging as log
import os
import re
import socket
import sys
import traceback

from argparse import ArgumentParser
from copy import copy
from ctypes import byref, cdll, create_string_buffer
from datetime import datetime
from doctest import testmod
from getpass import getuser
from hashlib import sha1
from multiprocessing import Pool, cpu_count
from platform import platform, python_version
from random import randint
from tempfile import gettempdir
from time import sleep

try:
    from urllib import request
    from subprocess import getoutput
    from shutil import disk_usage
    from io import StringIO  # pure-Python StringIO supports unicode.
    import resource  # windows dont have resource
except ImportError:
    request = getoutput = disk_usage = resource = None
    from StringIO import StringIO  # lint:ok


__version__ = '1.2.2'
__license__ = 'GPLv3+ LGPLv3+'
__author__ = 'Juan Carlos'
__email__ = 'juancarlospaco@gmail.com'
__url__ = 'https://github.com/juancarlospaco/css-html-js-minify'
__source__ = ('https://raw.githubusercontent.com/juancarlospaco/'
              'css-html-js-minify/master/css-html-js-minify.py')


EXTENDED_NAMED_COLORS, start_time = {  # 'Color Name String': (R, G, B)
    'azure': (240, 255, 255), 'beige': (245, 245, 220),
    'bisque': (255, 228, 196), 'blanchedalmond': (255, 235, 205),
    'brown': (165, 42, 42), 'burlywood': (222, 184, 135),
    'chartreuse': (127, 255, 0), 'chocolate': (210, 105, 30),
    'coral': (255, 127, 80), 'cornsilk': (255, 248, 220),
    'crimson': (220, 20, 60), 'cyan': (0, 255, 255), 'darkcyan': (0, 139, 139),
    'darkgoldenrod': (184, 134, 11), 'darkgray': (169, 169, 169),
    'darkgreen': (0, 100, 0), 'darkgrey': (169, 169, 169),
    'darkkhaki': (189, 183, 107), 'darkmagenta': (139, 0, 139),
    'darkolivegreen': (85, 107, 47), 'darkorange': (255, 140, 0),
    'darkorchid': (153, 50, 204), 'darkred': (139, 0, 0),
    'darksalmon': (233, 150, 122), 'darkseagreen': (143, 188, 143),
    'darkslategray': (47, 79, 79), 'darkslategrey': (47, 79, 79),
    'darkturquoise': (0, 206, 209), 'darkviolet': (148, 0, 211),
    'deeppink': (255, 20, 147), 'dimgray': (105, 105, 105),
    'dimgrey': (105, 105, 105), 'firebrick': (178, 34, 34),
    'forestgreen': (34, 139, 34), 'gainsboro': (220, 220, 220),
    'gold': (255, 215, 0), 'goldenrod': (218, 165, 32),
    'gray': (128, 128, 128), 'green': (0, 128, 0), 'grey': (128, 128, 128),
    'honeydew': (240, 255, 240), 'hotpink': (255, 105, 180),
    'indianred': (205, 92, 92), 'indigo': (75, 0, 130),
    'ivory': (255, 255, 240), 'khaki': (240, 230, 140),
    'lavender': (230, 230, 250), 'lavenderblush': (255, 240, 245),
    'lawngreen': (124, 252, 0), 'lemonchiffon': (255, 250, 205),
    'lightcoral': (240, 128, 128), 'lightcyan': (224, 255, 255),
    'lightgray': (211, 211, 211), 'lightgreen': (144, 238, 144),
    'lightgrey': (211, 211, 211), 'lightpink': (255, 182, 193),
    'lightsalmon': (255, 160, 122), 'lightseagreen': (32, 178, 170),
    'lightslategray': (119, 136, 153), 'lightslategrey': (119, 136, 153),
    'lime': (0, 255, 0), 'limegreen': (50, 205, 50), 'linen': (250, 240, 230),
    'magenta': (255, 0, 255), 'maroon': (128, 0, 0),
    'mediumorchid': (186, 85, 211), 'mediumpurple': (147, 112, 219),
    'mediumseagreen': (60, 179, 113), 'mediumspringgreen': (0, 250, 154),
    'mediumturquoise': (72, 209, 204), 'mediumvioletred': (199, 21, 133),
    'mintcream': (245, 255, 250), 'mistyrose': (255, 228, 225),
    'moccasin': (255, 228, 181), 'navy': (0, 0, 128),
    'oldlace': (253, 245, 230), 'olive': (128, 128, 0),
    'olivedrab': (107, 142, 35), 'orange': (255, 165, 0),
    'orangered': (255, 69, 0), 'orchid': (218, 112, 214),
    'palegoldenrod': (238, 232, 170), 'palegreen': (152, 251, 152),
    'paleturquoise': (175, 238, 238), 'palevioletred': (219, 112, 147),
    'papayawhip': (255, 239, 213), 'peachpuff': (255, 218, 185),
    'peru': (205, 133, 63), 'pink': (255, 192, 203), 'plum': (221, 160, 221),
    'purple': (128, 0, 128), 'rosybrown': (188, 143, 143),
    'saddlebrown': (139, 69, 19), 'salmon': (250, 128, 114),
    'sandybrown': (244, 164, 96), 'seagreen': (46, 139, 87),
    'seashell': (255, 245, 238), 'sienna': (160, 82, 45),
    'silver': (192, 192, 192), 'slategray': (112, 128, 144),
    'slategrey': (112, 128, 144), 'snow': (255, 250, 250),
    'springgreen': (0, 255, 127), 'teal': (0, 128, 128),
    'thistle': (216, 191, 216), 'tomato': (255, 99, 71),
    'turquoise': (64, 224, 208), 'violet': (238, 130, 238),
    'wheat': (245, 222, 179)}, datetime.now()


CSS_PROPS_TEXT = '''

alignment-adjust alignment-baseline animation animation-delay
animation-direction animation-duration animation-iteration-count
animation-name animation-play-state animation-timing-function appearance
azimuth

backface-visibility background background-blend-mode background-attachment
background-clip background-color background-image background-origin
background-position background-position-block background-position-inline
background-position-x background-position-y background-repeat background-size
baseline-shift bikeshedding bookmark-label bookmark-level bookmark-state
bookmark-target border border-bottom border-bottom-color
border-bottom-left-radius border-bottom-parts border-bottom-right-radius
border-bottom-style border-bottom-width border-clip border-clip-top
border-clip-right border-clip-bottom border-clip-left border-collapse
border-color border-corner-shape border-image border-image-outset
border-image-repeat border-image-slice border-image-source border-image-width
border-left border-left-color border-left-style border-left-parts
border-left-width border-limit border-parts border-radius border-right
border-right-color border-right-style border-right-width border-right-parts
border-spacing border-style border-top border-top-color border-top-left-radius
border-top-parts border-top-right-radius border-top-style border-top-width
border-width bottom box-decoration-break box-shadow box-sizing caption-side
clear clip color column-count column-fill column-gap column-rule
column-rule-color column-rule-style column-rule-width column-span column-width
columns content counter-increment counter-reset corners corner-shape
cue cue-after cue-before cursor

direction display drop-initial-after-adjust drop-initial-after-align
drop-initial-before-adjust drop-initial-before-align drop-initial-size
drop-initial-value

elevation empty-cells

flex flex-basis flex-direction flex-flow flex-grow flex-shrink flex-wrap fit
fit-position float font font-family font-size font-size-adjust font-stretch
font-style font-variant font-weight

grid-columns grid-rows

justify-content

hanging-punctuation height hyphenate-character hyphenate-resource hyphens

icon image-orientation image-resolution inline-box-align

left letter-spacing line-height line-stacking line-stacking-ruby
line-stacking-shift line-stacking-strategy linear-gradient list-style
list-style-image list-style-position list-style-type

margin margin-bottom margin-left margin-right margin-top marquee-direction
marquee-loop marquee-speed marquee-style max-height max-width min-height
min-width

nav-index

opacity orphans outline outline-color outline-offset outline-style
outline-width overflow overflow-style overflow-x overflow-y

padding padding-bottom padding-left padding-right padding-top page
page-break-after page-break-before page-break-inside pause pause-after
pause-before perspective perspective-origin pitch pitch-range play-during
position presentation-level

quotes

resize rest rest-after rest-before richness right rotation rotation-point
ruby-align ruby-overhang ruby-position ruby-span

size speak speak-header speak-numeral speak-punctuation speech-rate src
stress string-set

table-layout target target-name target-new target-position text-align
text-align-last text-decoration text-emphasis text-indent text-justify
text-outline text-shadow text-transform text-wrap top transform
transform-origin transition transition-delay transition-duration
transition-property transition-timing-function

unicode-bidi unicode-range

vertical-align visibility voice-balance voice-duration voice-family
voice-pitch voice-range voice-rate voice-stress voice-volume volume

white-space widows width word-break word-spacing word-wrap

z-index

'''  # Do Not compact this string, new lines are used to Group up stuff.


###############################################################################
# CSS minify


def _compile_props(props_text, grouped=False):
    """Take a list of props and prepare them."""
    props, prefixes = [], "-webkit-,-khtml-,-epub-,-moz-,-ms-,-o-,".split(",")
    for propline in props_text.strip().lower().splitlines():
        props += [pre + pro for pro in propline.split(" ") for pre in prefixes]
    props = filter(lambda line: not line.startswith('#'), props)
    if not grouped:
        props = list(filter(None, props))
        return props, [0]*len(props)
    final_props, groups, g_id = [], [], 0
    for prop in props:
        if prop.strip():
            final_props.append(prop)
            groups.append(g_id)
        else:
            g_id += 1
    return (final_props, groups)


def _prioritify(line_of_css, css_props_text_as_list):
    """Return args priority, priority is integer and smaller means higher."""
    sorted_css_properties, groups_by_alphabetic_order = css_props_text_as_list
    priority_integer, group_integer = 9999, 0
    for css_property in sorted_css_properties:
        if css_property.lower() == line_of_css.split(":")[0].lower().strip():
            priority_integer = sorted_css_properties.index(css_property)
            group_integer = groups_by_alphabetic_order[priority_integer]
            break
    return (priority_integer, group_integer)


def _props_grouper(props, pgs):
    """Return groups for properties."""
    if not props:
        return props
    #props = sorted([
        #_ if _.strip().endswith(";")
        #and not _.strip().endswith("*/") and not _.strip().endswith("/*")
        #else _.rstrip() + ";\n" for _ in props])
    props_pg = zip(map(lambda prop: _prioritify(prop, pgs), props), props)
    props_pg = sorted(props_pg, key=lambda item: item[0][1])
    props_by_groups = map(
        lambda item: list(item[1]),
        itertools.groupby(props_pg, key=lambda item: item[0][1]))
    props_by_groups = map(lambda item: sorted(
        item, key=lambda item: item[0][0]), props_by_groups)
    props = []
    for group in props_by_groups:
        group = map(lambda item: item[1], group)
        props += group
        props += ['\n']
    props.pop()
    return props


def sort_properties(css_unsorted_string):
    """CSS Property Sorter Function.

    This function will read buffer argument, split it to a list by lines,
    sort it by defined rule, and return sorted buffer if it's CSS property.
    This function depends on '_prioritify' function.
    """
    log.debug("Alphabetically Sorting all CSS / SCSS Properties.")
    css_pgs = _compile_props(CSS_PROPS_TEXT, grouped=False)  # Do Not Group.
    pattern = re.compile(r'(.*?{\r?\n?)(.*?)(}.*?)|(.*)',
                         re.DOTALL + re.MULTILINE)
    matched_patterns = pattern.findall(css_unsorted_string)
    sorted_patterns, sorted_buffer = [], css_unsorted_string
    RE_prop = re.compile(r'((?:.*?)(?:;)(?:.*?\n)|(?:.*))',
                         re.DOTALL + re.MULTILINE)
    if len(matched_patterns) != 0:
        for matched_groups in matched_patterns:
            sorted_patterns += matched_groups[0].splitlines(True)
            props = map(lambda line: line.lstrip('\n'),
                        RE_prop.findall(matched_groups[1]))
            props = list(filter(lambda line: line.strip('\n '), props))
            props = _props_grouper(props, css_pgs)
            sorted_patterns += props
            sorted_patterns += matched_groups[2].splitlines(True)
            sorted_patterns += matched_groups[3].splitlines(True)
        sorted_buffer = ''.join(sorted_patterns)
    return sorted_buffer


def remove_comments(css):
    """Remove all CSS comment blocks."""
    log.debug("Removing all Comments.")
    iemac, preserve = False, False
    comment_start = css.find("/*")
    while comment_start >= 0:  # Preserve comments that look like `/*!...*/`.
        # Slicing is used to make sure we dont get an IndexError.
        preserve = css[comment_start + 2:comment_start + 3] == "!"
        comment_end = css.find("*/", comment_start + 2)
        if comment_end < 0:
            if not preserve:
                css = css[:comment_start]
                break
        elif comment_end >= (comment_start + 2):
            if css[comment_end - 1] == "\\":
                # This is an IE Mac-specific comment; leave this one and the
                # following one alone.
                comment_start = comment_end + 2
                iemac = True
            elif iemac:
                comment_start = comment_end + 2
                iemac = False
            elif not preserve:
                css = css[:comment_start] + css[comment_end + 2:]
            else:
                comment_start = comment_end + 2
        comment_start = css.find("/*", comment_start)
    return css


def remove_unnecessary_whitespace(css):
    """Remove unnecessary whitespace characters."""
    log.debug("Removing all unnecessary white spaces.")

    def pseudoclasscolon(css):
        """Prevent 'p :link' from becoming 'p:link'.

        Translates 'p :link' into 'p ___PSEUDOCLASSCOLON___link'.
        This is translated back again later.
        """
        regex = re.compile(r"(^|\})(([^\{\:])+\:)+([^\{]*\{)")
        match = regex.search(css)
        while match:
            css = ''.join([
                css[:match.start()],
                match.group().replace(":", "___PSEUDOCLASSCOLON___"),
                css[match.end():]])
            match = regex.search(css)
        return css

    css = pseudoclasscolon(css)
    # Remove spaces from before things.
    css = re.sub(r"\s+([!{};:>\(\)\],])", r"\1", css)
    # If there is a `@charset`, then only allow one, and move to beginning.
    css = re.sub(r"^(.*)(@charset \"[^\"]*\";)", r"\2\1", css)
    css = re.sub(r"^(\s*@charset [^;]+;\s*)+", r"\1", css)
    # Put the space back in for a few cases, such as `@media screen` and
    # `(-webkit-min-device-pixel-ratio:0)`.
    css = re.sub(r"\band\(", "and (", css)
    # Put the colons back.
    css = css.replace('___PSEUDOCLASSCOLON___', ':')
    # Remove spaces from after things.
    css = re.sub(r"([!{}:;>\(\[,])\s+", r"\1", css)
    return css


def remove_unnecessary_semicolons(css):
    """Remove unnecessary semicolons."""
    log.debug("Removing all unnecessary semicolons.")
    return re.sub(r";+\}", "}", css)


def remove_empty_rules(css):
    """Remove empty rules."""
    log.debug("Removing all unnecessary empty rules.")
    return re.sub(r"[^\}\{]+\{\}", "", css)


def normalize_rgb_colors_to_hex(css):
    """Convert `rgb(51,102,153)` to `#336699`."""
    log.debug("Converting all rgba to hexadecimal color values.")
    regex = re.compile(r"rgb\s*\(\s*([0-9,\s]+)\s*\)")
    match = regex.search(css)
    while match:
        colors = map(lambda s: s.strip(), match.group(1).split(","))
        hexcolor = '#%.2x%.2x%.2x' % tuple(map(int, colors))
        css = css.replace(match.group(), hexcolor)
        match = regex.search(css)
    return css


def condense_zero_units(css):
    """Replace `0(px, em, %, etc)` with `0`."""
    log.debug("Condensing all zeroes on values.")
    return re.sub(r"([\s:])(0)(px|em|%|in|q|ch|cm|mm|pc|pt|ex|rem|s|ms|"
                  r"deg|grad|rad|turn|vw|vh|vmin|vmax|fr)", r"\1\2", css)


def condense_multidimensional_zeros(css):
    """Replace `:0 0 0 0;`, `:0 0 0;` etc. with `:0;`."""
    log.debug("Condensing all multidimensional zeroes on values.")
    return css.replace(":0 0 0 0;", ":0;").replace(
        ":0 0 0;", ":0;").replace(":0 0;", ":0;").replace(
            "background-position:0;", "background-position:0 0;").replace(
                "transform-origin:0;", "transform-origin:0 0;")


def condense_floating_points(css):
    """Replace `0.6` with `.6` where possible."""
    log.debug("Condensing all floating point values.")
    return re.sub(r"(:|\s)0+\.(\d+)", r"\1.\2", css)


def condense_hex_colors(css):
    """Shorten colors from #AABBCC to #ABC where possible."""
    log.debug("Condensing all hexadecimal color values.")
    regex = re.compile(
        r"""([^\"'=\s])(\s*)#([0-9a-f])([0-9a-f])([0-9a-f])"""
        + r"([0-9a-f])([0-9a-f])([0-9a-f])", re.I | re.S)
    match = regex.search(css)
    while match:
        first = match.group(3) + match.group(5) + match.group(7)
        second = match.group(4) + match.group(6) + match.group(8)
        if first.lower() == second.lower():
            css = css.replace(
                match.group(), match.group(1) + match.group(2) + '#' + first)
            match = regex.search(css, match.end() - 3)
        else:
            match = regex.search(css, match.end())
    return css


def condense_whitespace(css):
    """Condense multiple adjacent whitespace characters into one."""
    log.debug("Condensing all unnecessary white spaces.")
    return re.sub(r"\s+", " ", css)


def condense_semicolons(css):
    """Condense multiple adjacent semicolon characters into one."""
    log.debug("Condensing all unnecessary multiple adjacent semicolons.")
    return re.sub(r";;+", ";", css)


def wrap_css_lines(css, line_length=80):
    """Wrap the lines of the given CSS to an approximate length."""
    log.debug("Wrapping lines to ~{0} max line lenght.".format(line_length))
    lines, line_start = [], 0
    for i, char in enumerate(css):
        # Its safe to break after } characters.
        if char == '}' and (i - line_start >= line_length):
            lines.append(css[line_start:i + 1])
            line_start = i + 1
    if line_start < len(css):
        lines.append(css[line_start:])
    return '\n'.join(lines)


def condense_font_weight(css):
    """Condense multiple font weights into shorter integer equals."""
    log.debug("Condensing font weights on values.")
    return css.replace('font-weight:normal;', 'font-weight:400;').replace(
        'font-weight:bold;', 'font-weight:700;')


def condense_std_named_colors(css):
    """Condense named color values to shorter replacement using HEX."""
    log.debug("Condensing standard named color values.")
    for color_name, color_hexa in iter(tuple({
        ':aqua;': ':#0ff;', ':blue;': ':#00f;',
            ':fuchsia;': ':#f0f;', ':yellow;': ':#ff0;'}.items())):
        css = css.replace(color_name, color_hexa)
    return css


def condense_xtra_named_colors(css):
    """Condense named color values to shorter replacement using HEX."""
    log.debug("Condensing extended named color values.")
    for k, v in iter(tuple(EXTENDED_NAMED_COLORS.items())):
        same_color_but_rgb = 'rgb({0},{1},{2})'.format(v[0], v[1], v[2])
        if len(k) > len(same_color_but_rgb):
            css = css.replace(k, same_color_but_rgb)
    return css


def remove_url_quotes(css):
    """Fix for url() does not need quotes."""
    log.debug("Removing quotes from url.")
    return re.sub(r'url\((["\'])([^)]*)\1\)', r'url(\2)', css)


def condense_border_none(css):
    """Condense border:none; to border:0;."""
    log.debug("Condense borders values.")
    return css.replace("border:none;", "border:0;")


def add_encoding(css):
    """Add @charset 'UTF-8'; if missing."""
    log.debug("Adding encoding declaration if needed.")
    return "@charset utf-8;" + css if "@charset" not in css.lower() else css


def restore_needed_space(css):
    """Fix CSS for some specific cases where a white space is needed."""
    return css.replace("!important", " !important").replace(  # !important
        "@media(", "@media (").replace(  # media queries # jpeg > jpg
            "data:image/jpeg;base64,", "data:image/jpg;base64,").rstrip("\n;")


def unquote_selectors(css):
    """Fix CSS for some specific selectors where Quotes is not needed."""
    log.debug("Removing unnecessary Quotes on selectors of CSS classes.")
    return re.compile('([a-zA-Z]+)="([a-zA-Z0-9-_\.]+)"]').sub(r'\1=\2]', css)


def css_minify(css, wrap=False, comments=False, sort=False):
    """Minify CSS main function."""
    log.info("Compressing CSS...")
    css = remove_comments(css) if not comments else css
    css = sort_properties(css) if sort else css
    css = unquote_selectors(css)
    css = condense_whitespace(css)
    css = remove_url_quotes(css)
    css = condense_xtra_named_colors(css)
    css = condense_font_weight(css)
    css = remove_unnecessary_whitespace(css)
    css = condense_std_named_colors(css)
    css = remove_unnecessary_semicolons(css)
    css = condense_zero_units(css)
    css = condense_multidimensional_zeros(css)
    css = condense_floating_points(css)
    css = normalize_rgb_colors_to_hex(css)
    css = condense_hex_colors(css)
    css = condense_border_none(css)
    css = wrap_css_lines(css, 80) if wrap else css
    css = condense_semicolons(css)
    css = add_encoding(css)
    css = restore_needed_space(css)
    log.info("Finished compressing CSS !.")
    return css.strip()


##############################################################################
# HTML Minify


def condense_html_whitespace(html):
    """Condense HTML, but be safe first if it have textareas or pre tags.

    >>> condense_html_whitespace('<i>  <b>    <a> test </a>    </b> </i><br>')
    '<i><b><a> test </a></b></i><br>'
    """  # first space between tags, then empty new lines and in-between.
    log.debug("Removing unnecessary HTML White Spaces and Empty New Lines.")
    is_ok = "<textarea" not in html.lower() and "<pre" not in html.lower()
    html = re.sub(r'>\s+<', '> <', html) if is_ok else html
    return re.sub(r'\s{2,}|[\r\n]', ' ', html) if is_ok else html.strip()


def condense_style(html):
    """Condense style html tags.

    >>> condense_style('<style type="text/css">*{border:0}</style><p>a b c')
    '<style>*{border:0}</style><p>a b c'
    """  # May look silly but Emmet does this and is wrong.
    log.debug("Condensing HTML Style CSS tags.")
    return html.replace('<style type="text/css">', '<style>').replace(
        "<style type='text/css'>", '<style>').replace(
            "<style type=text/css>", '<style>')


def condense_script(html):
    """Condense script html tags.

    >>> condense_script('<script type="text/javascript"> </script><p>a b c')
    '<script> </script><p>a b c'
    """  # May look silly but Emmet does this and is wrong.
    log.debug("Condensing HTML Script JS tags.")
    return html.replace('<script type="text/javascript">', '<script>').replace(
        "<style type='text/javascript'>", '<script>').replace(
            "<style type=text/javascript>", '<script>')


def clean_unneeded_html_tags(html):
    """Clean unneeded optional html tags.

    >>> clean_unneeded_html_tags('a<body></img></td>b</th></tr></hr></br>c')
    'abc'
    """
    log.debug("Removing unnecessary optional HTML tags.")
    for tag_to_remove in ("""</area> </base> <body> </body> </br> </col>
        </colgroup> </dd> </dt> <head> </head> </hr> <html> </html> </img>
        </input> </li> </link> </meta> </option> </param> 
        </td> </tfoot> </th> </thead> </tr> </basefont> </isindex> </param>
        """.split()):
            html = html.replace(tag_to_remove, '')
    return html  # May look silly but Emmet does this and is wrong.


def remove_html_comments(html):
    """Remove all HTML comments, Keep all for Grunt, Grymt and IE.

    >>> _="<!-- build:dev -->a<!-- endbuild -->b<!--[if IE 7]>c<![endif]--> "
    >>> _+= "<!-- kill me please -->keep" ; remove_html_comments(_)
    '<!-- build:dev -->a<!-- endbuild -->b<!--[if IE 7]>c<![endif]--> keep'
    """  # Grunt uses comments to as build arguments, bad practice but still.
    log.debug("""Removing all unnecessary HTML comments; Keep all containing:
    'build:', 'endbuild', '<!--[if]>', '<![endif]-->' for Grunt/Grymt, IE.""")
    return re.compile('<!-- [^(build|endbuild)].*? -->', re.I).sub('', html)


def unquote_html_attributes(html):
    """Remove all HTML quotes on attibutes if possible.

    >>> unquote_html_attributes('<img   width="9" height="5" data-foo="0"  >')
    '<img width=9 height=5 data-foo=0 >'
    """  # data-foo=0> might cause errors on IE, we leave 1 space data-foo=0 >
    log.debug("Removing unnecessary Quotes on attributes of HTML tags.")
    # cache all regular expressions on variables before we enter the for loop.
    any_tag = re.compile(r"<\w.*?>", re.I | re.MULTILINE | re.DOTALL)
    space = re.compile(r' \s+|\s +', re.MULTILINE)
    space1 = re.compile(r'\w\s+\w', re.MULTILINE)
    space2 = re.compile(r'"\s+>', re.MULTILINE)
    space3 = re.compile(r"'\s+>", re.MULTILINE)
    space4 = re.compile('"\s\s+\w+="|\'\s\s+\w+=\'|"\s\s+\w+=|\'\s\s+\w+=',
                        re.MULTILINE)
    space6 = re.compile(r"\d\s+>", re.MULTILINE)
    quotes_in_tag = re.compile('([a-zA-Z]+)="([a-zA-Z0-9-_\.]+)"')
    # iterate on a for loop cleaning stuff up on the html markup.
    for tag in iter(any_tag.findall(html)):
        # exceptions of comments and closing tags
        if tag.startswith('<!') or tag.find('</') > -1:
            continue
        original = tag
        # remove white space inside the tag itself
        tag = space2.sub('" >', tag)  # preserve 1 white space is safer
        tag = space3.sub("' >", tag)
        for each in space1.findall(tag) + space6.findall(tag):
            tag = tag.replace(each, space.sub(' ', each))
        for each in space4.findall(tag):
            tag = tag.replace(each, each[0] + ' ' + each[1:].lstrip())
        # remove quotes on some attributes
        tag = quotes_in_tag.sub(r'\1=\2', tag)
        if original != tag:  # has the tag been improved ?
            html = html.replace(original, tag)
    return html.strip()


def html_minify(html, comments=False):
    """Minify HTML main function.

    >>> html_minify(' <p  width="9" height="5"  > <!-- a --> b </p> c <br> ')
    '<p width=9 height=5 > b c <br>'
    """
    log.info("Compressing HTML...")
    html = remove_html_comments(html) if not comments else html
    html = condense_style(html)
    html = condense_script(html)
    html = clean_unneeded_html_tags(html)
    html = condense_html_whitespace(html)
    html = unquote_html_attributes(html)
    log.info("Finished compressing HTML !.")
    return html.strip()


##############################################################################
# JS Minify


def simple_replacer_js(js):
    """Force strip simple replacements from Javascript."""
    log.debug("Force strip simple replacements from Javascript.")
    return condense_semicolons(js.replace("debugger;", ";").replace(
        ";}", "}").replace("; ", ";").replace(" ;", ";").rstrip("\n;"))


def js_minify(js):
    """Return a minified version of the Javascript string."""
    log.info("Compressing Javascript...")
    ins, outs = StringIO(js), StringIO()
    JavascriptMinify(ins, outs).minify()
    return force_single_line_js(outs.getvalue())


def force_single_line_js(js):
    """Force Javascript to a single line, even if need to add semicolon."""
    log.debug("Forcing JS from ~{0} to 1 Line.".format(len(js.splitlines())))
    return ";".join(js.splitlines()) if len(js.splitlines()) > 1 else js


# regular expressions to find and work with Javascript functions and variables
function_start_regex = re.compile('(function[ \w+\s*]\(([^\)]*)\)\s*{)')
function_start_regex = re.compile('(function(\s+\w+|)\s*\(([^\)]*)\)\s*{)')


def _find_functions(whole):
    """Find function() on Javascript code."""
    for res in function_start_regex.findall(whole):
        function_start, function_name, params = res
        params_split = [x.strip() for x in params.split(',')]
        stack, code, core_code = 1, function_start, ''
        start = whole.find(function_start) + len(code)
        while stack > 0:
            try:
                next_char = whole[start]
            except IndexError:  # dont worry we will obfuscte the one we found
                return  # sometimes fails to find all functions on big files
            core_code += next_char
            if next_char == '{':
                stack += 1
            elif next_char == '}':
                stack -= 1
            start += 1
        yield (params, params_split, core_code[:-1], function_start)


def slim_params(code):
    """Compress params on Javascript code functions.

    >>> slim_params('function f(large_name,is_large){large_name*is_large}')
    'function f(_0,_1){_0*_1}'
    """
    old_functions, new_code = {}, code
    for params, params_split, core, function_start in _find_functions(code):
        params_split_use = [x for x in params_split if len(x) > 1]
        _param_regex = '|'.join([r'\b%s\b' % x for x in params_split_use])
        param_regex, new_params = re.compile(_param_regex), {}
        for i in range(len(params_split_use)):
            new_params[params_split[i]] = '_{}'.format(i)
        replacer_1 = lambda __match: new_params.get(__match.group())
        new_core, _params = param_regex.sub(replacer_1, core), []
        for p in params_split:
            _params.append(new_params.get(p, p))
        new_function = function_start.replace(
            params, ','.join(_params)) + new_core + '}'
        old_function = function_start + core + '}'
        old_functions[old_function] = new_function
    regex = '|'.join([re.escape(x) for x in old_functions.keys()])
    replacer_2 = lambda __match: old_functions.get(__match.group())
    return re.sub(regex, replacer_2, new_code)


class NamesGenerator:

    """Class to generate names for Javascript code function variables."""

    def __init__(self):
        """Init class, setup basic variables."""
        self.i, self.pool = 0, list('ABCDEFGHIJKLMNOPQRSTUVWXYZ')

    def next(self):
        """Work with next items.

        >>> _=NamesGenerator();(_.next(),_.next(),_.next(),_.next(),_.next())
        ('_A', '_B', '_C', '_D', '_E')
        """
        try:
            e = self.pool[self.i]
            self.i = self.i + 1
        except IndexError:
            if not hasattr(self, 'j'):
                self.j = 0
                self.pool.extend([x.lower() for x in self.pool])
            try:
                e = self.pool[self.i % len(self.pool)] + self.pool[self.j]
                self.j = self.j + 1
            except IndexError:
                self.i += 1
                self.j = 0
                return self.next()
        return '_{}'.format(e)


def slim_func_names(js):
    """Compress Javascript variable names inside functions.

    >>> slim_func_names('function longName(p1,p2){return p1*p2}longName(2,4)')
    'function _A(p1,p2){return p1*p2}_A(2,4);var longName=_A;'
    """
    renamed_func, functions = [], re.compile('(function (\w+)\()').findall(js)
    new_names_generator = NamesGenerator()
    for whole_func, func_name in functions:
        count = js.count(func_name)  # more than 1 mention of the function
        if len(func_name) > 3 and count > 1:  # function name larger than 3
            new_name = new_names_generator.next()
            if re.findall(r'\b%s\b' % re.escape(new_name), js):
                continue
            js = re.sub(r'\b%s\b' % re.escape(func_name), new_name, js)
            renamed_func.append((func_name, new_name))
    list_of_replacements = ['{}={}'.format(x, y) for (x, y) in renamed_func]
    js_function_name_replacements = ';var {};'.format(  # ;var a=b,c=d; or ''
        ','.join(list_of_replacements)) if len(list_of_replacements) else ""
    return js + js_function_name_replacements


def js_minify2(js):
    """Compress variables and functions names.

    >>> js_minify2('function foo(long_variable_name,bar){console.log(bar);};')
    'function foo(_0,_1){console.log(_1);};'
    """
    log.debug("Obfuscating Javascript variables names inside functions.")
    # if eval() or with{} is used on JS is not too Safe to Obfuscate stuff.
    is_ok = "eval(" not in js and "with{" not in js and "with {" not in js
    return slim_func_names(slim_params(js)) if is_ok else js.strip()


class JavascriptMinify(object):

    """Minify an input stream of Javascript, writing to an output stream."""

    def __init__(self, instream=None, outstream=None):
        """Init class."""
        self.ins, self.outs = instream, outstream

    def minify(self, instream=None, outstream=None):
        """Minify Javascript using StringIO."""
        if instream and outstream:
            self.ins, self.outs = instream, outstream
        write, read = self.outs.write, self.ins.read
        space_strings = ("abcdefghijklmnopqrstuvwxyz"
                         "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_$\\")
        starters, enders = '{[(+-', '}])+-"\''
        newlinestart_strings = starters + space_strings
        newlineend_strings = enders + space_strings
        do_newline, do_space = False, False
        doing_single_comment, doing_multi_comment = False, False
        previous_before_comment, in_quote = '', ''
        in_re, quote_buf = False, []
        previous = read(1)
        next1 = read(1)
        if previous == '/':
            if next1 == '/':
                doing_single_comment = True
            elif next1 == '*':
                doing_multi_comment = True
            else:
                write(previous)
        elif not previous:
            return
        elif previous >= '!':
            if previous in "'\"":
                in_quote = previous
            write(previous)
            previous_non_space = previous
        else:
            previous_non_space = ' '
        if not next1:
            return
        while True:
            next2 = read(1)
            if not next2:
                last = next1.strip()
                conditional_1 = (doing_single_comment or doing_multi_comment)
                if not conditional_1 and last not in ('', '/'):
                    write(last)
                break
            if doing_multi_comment:
                if next1 == '*' and next2 == '/':
                    doing_multi_comment = False
                    next2 = read(1)
            elif doing_single_comment:
                if next1 in '\r\n':
                    doing_single_comment = False
                    while next2 in '\r\n':
                        next2 = read(1)
                        if not next2:
                            break
                    if previous_before_comment in ')}]':
                        do_newline = True
                    elif previous_before_comment in space_strings:
                        write('\n')
            elif in_quote:
                quote_buf.append(next1)

                if next1 == in_quote:
                    numslashes = 0
                    for c in reversed(quote_buf[:-1]):
                        if c != '\\':
                            break
                        else:
                            numslashes += 1
                    if numslashes % 2 == 0:
                        in_quote = ''
                        write(''.join(quote_buf))
            elif next1 in '\r\n':
                conditional_2 = previous_non_space in newlineend_strings
                if conditional_2 or previous_non_space > '~':
                    while 1:
                        if next2 < '!':
                            next2 = read(1)
                            if not next2:
                                break
                        else:
                            conditional_3 = next2 in newlinestart_strings
                            if conditional_3 or next2 > '~' or next2 == '/':
                                do_newline = True
                            break
            elif next1 < '!' and not in_re:
                conditional_4 = next2 in space_strings or next2 > '~'
                conditional_5 = previous_non_space in space_strings
                conditional_6 = previous_non_space > '~'
                if (conditional_5 or conditional_6) and (conditional_4):
                    do_space = True
            elif next1 == '/':
                if in_re:
                    if previous != '\\':
                        in_re = False
                    write('/')
                elif next2 == '/':
                    doing_single_comment = True
                    previous_before_comment = previous_non_space
                elif next2 == '*':
                    doing_multi_comment = True
                else:
                    in_re = previous_non_space in '(,=:[?!&|'
                    write('/')
            else:
                if do_space:
                    do_space = False
                    write(' ')
                if do_newline:
                    write('\n')
                    do_newline = False
                write(next1)
                if not in_re and next1 in "'\"":
                    in_quote = next1
                    quote_buf = []
            previous = next1
            next1 = next2
            if previous >= '!':
                previous_non_space = previous


##############################################################################


def walkdir_to_filelist(where, target, omit):
    """Perform full walk of where, gather full path of all files."""
    log.debug("Scan {},searching {},ignoring {}".format(where, target, omit))
    return tuple([os.path.join(r, f) for r, d, fs in os.walk(where)
                  for f in fs if not f.startswith('.') and not f.endswith(omit)
                  and f.endswith(target)])  # only target files,no hidden files


def process_multiple_files(file_path):
    """Process multiple CSS, JS, HTML files with multiprocessing."""
    log.debug("Process {} is Compressing {}.".format(os.getpid(), file_path))
    if args.watch:
        previous = int(os.stat(file_path).st_mtime)
        log.info("Process {} is Watching {}.".format(os.getpid(), file_path))
        while True:
            actual = int(os.stat(file_path).st_mtime)
            if previous == actual:
                sleep(60)
            else:
                previous = actual
                log.debug("Modification detected on {0}.".format(file_path))
                check_working_folder(os.path.dirname(file_path))
                if file_path.endswith(".css"):
                    process_single_css_file(file_path)
                elif file_path.endswith(".js"):
                    process_single_js_file(file_path)
                else:
                    process_single_html_file(file_path)
    else:
        if file_path.endswith(".css"):
            process_single_css_file(file_path)
        elif file_path.endswith(".js"):
            process_single_js_file(file_path)
        else:
            process_single_html_file(file_path)


def prefixer_extensioner(file_path, old, new, file_content=None):
    """Take a file path and safely preppend a prefix and change extension.

    This is needed because filepath.replace('.foo', '.bar') sometimes may
    replace '/folder.foo/file.foo' into '/folder.bar/file.bar' wrong!.
    >>> prefixer_extensioner('/tmp/test.js', '.js', '.min.js')
    '/tmp/test.min.js'
    """
    log.debug("Prepending '{}' Prefix to {}.".format(new.upper(), file_path))
    global args
    extension = os.path.splitext(file_path)[1].lower().replace(old, new)
    filenames = os.path.splitext(os.path.basename(file_path))[0]
    filenames = args.prefix + filenames if args.prefix else filenames
    if args.hash and file_content:  # http://stackoverflow.com/a/25568916
        filenames += "-" + sha1(file_content.encode("utf-8")).hexdigest()[:11]
        log.debug("Appending SHA1 HEX-Digest Hash to '{}'.".format(file_path))
    dir_names = os.path.dirname(file_path)
    file_path = os.path.join(dir_names, filenames + extension)
    return file_path


def process_single_css_file(css_file_path):
    """Process a single CSS file."""
    log.info("Processing CSS file: {0}.".format(css_file_path))
    global args
    try:  # Python3
        with open(css_file_path, encoding="utf-8-sig") as css_file:
            original_css = css_file.read()
    except:  # Python2
        with open(css_file_path) as css_file:
            original_css = css_file.read()
    log.debug("INPUT: Reading CSS file {}.".format(css_file_path))
    minified_css = css_minify(original_css, wrap=args.wrap,
                              comments=args.comments, sort=args.sort)
    if args.timestamp:
        taim = "/* {0} */ ".format(datetime.now().isoformat()[:-7].lower())
        minified_css = taim + minified_css
    min_css_file_path = prefixer_extensioner(
        css_file_path, ".css", ".css" if args.overwrite else ".min.css",
        original_css)
    if only_on_py3(args.gzip):
        gz_file_path = prefixer_extensioner(
            css_file_path, ".css",
            ".css.gz" if args.overwrite else ".min.css.gz", original_css)
        log.debug("OUTPUT: Writing gZIP CSS Minified {}.".format(gz_file_path))
    try:
        with open(min_css_file_path, "w", encoding="utf-8") as output_file:
            output_file.write(minified_css)
        if only_on_py3(args.gzip):
            with gzip.open(gz_file_path, "wt", encoding="utf-8") as output_gz:
                output_gz.write(minified_css)
    except:
        with open(min_css_file_path, "w") as output_file:
            output_file.write(minified_css)
        if only_on_py3(args.gzip):
            with gzip.open(gz_file_path, "w") as output_gz:
                output_gz.write(minified_css)
    log.debug("OUTPUT: Writing CSS Minified {0}.".format(min_css_file_path))


def process_single_html_file(html_file_path):
    """Process a single HTML file."""
    log.info("Processing HTML file: {0}.".format(html_file_path))
    try:  # Python3
        with open(html_file_path, encoding="utf-8-sig") as html_file:
            minified_html = html_minify(html_file.read(),
                                        comments=only_on_py3(args.comments))
    except:  # Python2
        with open(html_file_path) as html_file:
            minified_html = html_minify(html_file.read(),
                                        comments=only_on_py3(args.comments))
    log.debug("INPUT: Reading HTML file {0}.".format(html_file_path))
    html_file_path = prefixer_extensioner(
        html_file_path, ".html" if args.overwrite else ".htm", ".html")
    try:  # Python3
        with open(html_file_path, "w", encoding="utf-8") as output_file:
            output_file.write(minified_html)
    except:  # Python2
        with open(html_file_path, "w") as output_file:
            output_file.write(minified_html)
    log.debug("OUTPUT: Writing HTML Minified {0}.".format(html_file_path))


def process_single_js_file(js_file_path):
    """Process a single JS file."""
    log.info("Processing JS file: {0}.".format(js_file_path))
    try:  # Python3
        with open(js_file_path, encoding="utf-8-sig") as js_file:
            original_js = js_file.read()
    except:  # Python2
        with open(js_file_path) as js_file:
            original_js = js_file.read()
    log.debug("INPUT: Reading JS file {0}.".format(js_file_path))
    if args.obfuscate:  # with obfuscation
        minified_js = simple_replacer_js(js_minify(js_minify2(original_js)))
    else:  # without obfuscation
        minified_js = js_minify(original_js)
    if args.timestamp:
        taim = "/* {} */ ".format(datetime.now().isoformat()[:-7].lower())
        minified_js = taim + minified_js
    min_js_file_path = prefixer_extensioner(
        js_file_path, ".js", ".js" if args.overwrite else ".min.js",
        original_js)
    if only_on_py3(args.gzip):
        gz_file_path = prefixer_extensioner(
            js_file_path, ".js", ".js.gz" if args.overwrite else ".min.js.gz",
            original_js)
        log.debug("OUTPUT: Writing gZIP JS Minified {}.".format(gz_file_path))
    try:  # Python3
        with open(min_js_file_path, "w", encoding="utf-8") as output_file:
            output_file.write(minified_js)
        if only_on_py3(args.gzip):
            with gzip.open(gz_file_path, "wt", encoding="utf-8") as output_gz:
                output_gz.write(minified_js)
    except:  # Python2
        with open(min_js_file_path, "w") as output_file:
            output_file.write(minified_js)
        if only_on_py3(args.gzip):
            with gzip.open(gz_file_path, "w") as output_gz:
                output_gz.write(minified_js)
    log.debug("OUTPUT: Writing JS Minified {0}.".format(min_js_file_path))


def check_for_updates():
    """Method to check for updates from Git repo versus this version."""
    last_version = str(request.urlopen(__source__).read().decode("utf8"))
    if str(open(__file__).read()) != last_version:
        log.warning("Theres new Version available!, Update from " + __source__)
    else:
        log.info("No new updates!,You have the lastest version of this app.")


def only_on_py3(boolean_argument=True):
    """Deprecate features if not using Python >= 3, to motivate migration."""
    if isinstance(boolean_argument, (tuple, list)):  # argument is iterable.
        boolean_argument = all(boolean_argument)
    else:  # argument is boolean, or evaluate as boolean, even if is not.
        boolean_argument = bool(boolean_argument)
    if sys.version_info.major >= 3:
        return boolean_argument  # good to go
    else:  # Migrate to python 3, is free and easy, get a virtualenv at least.
        log.critical("Feature only available on Python 3, feature ignored !.")
        log.debug("Please Migrate to Python 3 for better User Experience...")
        return False


def check_working_folder(folder_to_check=os.path.expanduser("~")):
    """Check working folder,passed argument,for everything that can go wrong.

    >>> check_working_folder()
    True
    """
    folder_to_check = os.path.abspath(folder_to_check)  # See Bug #20 on WinOS
    log.debug("Checking the Working Folder: '{0}'".format(folder_to_check))
    # What if folder is not a string.
    if not isinstance(folder_to_check, str) :
        log.critical("Folder {0} is not String type!.".format(folder_to_check))
        return False
    elif os.path.isfile(folder_to_check):
        log.info("Folder {0} is File or Relative Path".format(folder_to_check))
        return True
    # What if folder is not a folder.
    elif not os.path.isdir(folder_to_check):
        log.critical("Folder {0} does not exist !.".format(folder_to_check))
        return False
    # What if destination folder is not Readable by the user.
    elif not os.access(folder_to_check, os.R_OK):
        log.critical("Folder {0} not Readable !.".format(folder_to_check))
        return False
    # What if destination folder is not Writable by the user.
    elif not os.access(folder_to_check, os.W_OK):
        log.critical("Folder {0} Not Writable !.".format(folder_to_check))
        return False
    elif disk_usage and os.path.exists(folder_to_check):
        hdd = int(disk_usage(folder_to_check).free / 1024 / 1024 / 1024)
        if hdd:  # > 1 Gb
            log.info("Total Free Space: ~{0} GigaBytes.".format(hdd))
            return True
        else:  # < 1 Gb
            log.critical("Total Free Space is < 1 GigaByte; Epic Fail !.")
            return False
    return False


def make_root_check_and_encoding_debug():
    """Debug and Log Encodings and Check for root/administrator,return Boolean.

    >>> make_root_check_and_encoding_debug()
    True
    """
    log.info(__doc__)
    log.debug("Python {0} on {1}.".format(python_version(), platform()))
    log.debug("STDIN Encoding: {0}.".format(sys.stdin.encoding))
    log.debug("STDERR Encoding: {0}.".format(sys.stderr.encoding))
    log.debug("STDOUT Encoding:{}".format(getattr(sys.stdout, "encoding", "")))
    log.debug("Default Encoding: {0}.".format(sys.getdefaultencoding()))
    log.debug("FileSystem Encoding: {0}.".format(sys.getfilesystemencoding()))
    log.debug("PYTHONIOENCODING Encoding: {0}.".format(
        os.environ.get("PYTHONIOENCODING", None)))
    os.environ["PYTHONIOENCODING"], sys.dont_write_bytecode = "utf-8", True
    if not sys.platform.startswith("win"):  # root check
        if not os.geteuid():
            log.critical("Runing as root is not Recommended,NOT Run as root!.")
            return False
    elif sys.platform.startswith("win"):  # administrator check
        if getuser().lower().startswith("admin"):
            log.critical("Runing as Administrator is not Recommended!.")
            return False
    return True


def set_process_name_and_cpu_priority(name):
    """Set process name and cpu priority.

    >>> set_process_name_and_cpu_priority("test_test")
    True
    """
    try:
        os.nice(19)  # smooth cpu priority
        libc = cdll.LoadLibrary("libc.so.6")  # set process name
        buff = create_string_buffer(len(name.lower().strip()) + 1)
        buff.value = bytes(name.lower().strip().encode("utf-8"))
        libc.prctl(15, byref(buff), 0, 0, 0)
    except Exception:
        return False  # this may fail on windows and its normal, so be silent.
    else:
        log.debug("Process Name set to: {0}.".format(name))
        return True


def set_single_instance(name, single_instance=True, port=8888):
    """Set process name and cpu priority,return socket.socket object or None"""
    __lock = None
    if single_instance:
        try:  # Single instance app ~crossplatform, uses udp socket.
            log.info("Creating Abstract UDP Socket Lock for Single Instance.")
            __lock = socket.socket(
                socket.AF_UNIX if sys.platform.startswith("linux")
                else socket.AF_INET, socket.SOCK_STREAM)
            __lock.bind(
                "\0_{name}__lock".format(name=str(name).lower().strip())
                if sys.platform.startswith("linux") else ("127.0.0.1", port))
        except socket.error as e:
            log.warning(e)
        else:
            log.info("Socket Lock for Single Instance: {0}.".format(__lock))
    return __lock


def make_logger(name=str(os.getpid())):
    """Build and return a Logging Logger."""
    if not sys.platform.startswith("win") and sys.stderr.isatty():
        def add_color_emit_ansi(fn):
            """Add methods we need to the class."""
            def new(*args):
                """Method overload."""
                if len(args) == 2:
                    new_args = (args[0], copy(args[1]))
                else:
                    new_args = (args[0], copy(args[1]), args[2:])
                if hasattr(args[0], 'baseFilename'):
                    return fn(*args)
                levelno = new_args[1].levelno
                if levelno >= 50:
                    color = '\x1b[31;5;7m\n '  # blinking red with black
                elif levelno >= 40:
                    color = '\x1b[31m'  # red
                elif levelno >= 30:
                    color = '\x1b[33m'  # yellow
                elif levelno >= 20:
                    color = '\x1b[32m'  # green
                elif levelno >= 10:
                    color = '\x1b[35m'  # pink
                else:
                    color = '\x1b[0m'  # normal
                try:
                    new_args[1].msg = color + str(new_args[1].msg) + ' \x1b[0m'
                except Exception as reason:
                    print(reason)  # Do not use log here.
                return fn(*new_args)
            return new
        log.StreamHandler.emit = add_color_emit_ansi(log.StreamHandler.emit)
    log_file = os.path.join(gettempdir(), str(name).lower().strip() + ".log")
    log.basicConfig(level=-1, filemode="w", filename=log_file)
    log.getLogger().addHandler(log.StreamHandler(sys.stderr))
    adrs = "/dev/log" if sys.platform.startswith("lin") else "/var/run/syslog"
    try:
        handler = log.handlers.SysLogHandler(address=adrs)
    except:
        log.debug("Unix SysLog Server not found, ignored Logging to SysLog.")
    else:
        log.getLogger().addHandler(handler)
    log.debug("Logger created with Log file at: {0}.".format(log_file))
    return log


def make_post_execution_message(app=__doc__.splitlines()[0].strip()):
    """Simple Post-Execution Message with information about RAM and Time."""
    ram_use, ram_all = 0, 0
    use = 0
    al = 0
    msg = "end"
    if sys.platform.startswith("linux"):
        use = int(resource.getrusage(resource.RUSAGE_SELF).ru_maxrss *
                    resource.getpagesize() / 1024 / 1024 if resource else 0)
        al = int(os.sysconf('SC_PAGE_SIZE') * os.sysconf('SC_PHYS_PAGES')
                      / 1024 / 1024 if hasattr(os, "sysconf") else 0)
        msg = "Total Maximum RAM Memory used: ~{0} of {1}MegaBytes".format(use, al)
        log.info(msg)
    if start_time and datetime:
        log.info("Total Working Time: {0}".format(datetime.now() - start_time))
    if randint(0, 100) < 25:  # ~25% chance to see the message,dont get on logs
        print("Thanks for using this App,share your experience! {0}".format("""
        Twitter: https://twitter.com/home?status=I%20Like%20{n}!:%20{u}
        Facebook: https://www.facebook.com/share.php?u={u}&t=I%20Like%20{n}
        G+: https://plus.google.com/share?url={u}""".format(u=__url__, n=app)))
    return msg


def make_arguments_parser():
    """Build and return a command line agument parser."""
    parser = ArgumentParser(description=__doc__, epilog="""CSS-HTML-JS-Minify:
    Takes a file or folder full path string and process all CSS/HTML/JS found.
    If argument is not file/folder will fail. Check Updates works on Python3.
    Std-In to Std-Out is deprecated since it may fail with unicode characters.
    SHA1 HEX-Digest 11 Chars Hash on Filenames is used for Server Cache.
    CSS Properties are Alpha-Sorted, to help spot cloned ones, Selectors not.
    Watch works for whole folders, with minimum of ~60 Secs between runs.""")
    parser.add_argument('--version', action='version', version=__version__)
    parser.add_argument('fullpath', metavar='fullpath', type=str,
                        help='Full path to local file or folder.')
    parser.add_argument('--wrap', action='store_true',
                        help="Wrap output to ~80 chars per line, CSS only.")
    parser.add_argument('--prefix', type=str,
                        help="Prefix string to prepend on output filenames.")
    parser.add_argument('--timestamp', action='store_true',
                        help="Add a Time Stamp on all CSS/JS output files.")
    parser.add_argument('--quiet', action='store_true', help="Quiet, Silent.")
    parser.add_argument('--obfuscate', action='store_true',
                        help="Obfuscate Javascript. JS only. (Recommended).")
    parser.add_argument('--checkupdates', action='store_true',
                        help="Check for updates from internet while running.")
    parser.add_argument('--tests', action='store_true', help="Run Unit Tests.")
    parser.add_argument('--hash', action='store_true',
                        help="Add SHA1 HEX-Digest 11chars Hash to Filenames.")
    parser.add_argument('--gzip', action='store_true',
                        help="GZIP Minified files as '*.gz', CSS/JS only.")
    parser.add_argument('--sort', action='store_true',
                        help="Alphabetically Sort CSS Properties, CSS only.")
    parser.add_argument('--comments', action='store_true',
                        help="Keep comments, CSS/HTML only (Not Recommended)")
    parser.add_argument('--overwrite', action='store_true',
                        help="Force overwrite all in-place (Not Recommended)")
    parser.add_argument('--after', type=str,
                        help="Command to execute after run (Experimental).")
    parser.add_argument('--before', type=str,
                        help="Command to execute before run (Experimental).")
    parser.add_argument('--watch', action='store_true', help="Watch changes.")
    parser.add_argument('--multiple', action='store_true',
                        help="Allow Multiple instances (Not Recommended).")
    parser.add_argument('--_42', action='store_true')
    global args
    args = parser.parse_args()


def main():
    """Main Loop."""
    make_arguments_parser()
    make_logger("css-html-js-minify")
    make_root_check_and_encoding_debug()
    set_process_name_and_cpu_priority("css-html-js-minify")
    set_single_instance("css-html-js-minify")
    if args._42:  # Resynchronize flux capacitor.
        print((lambda r: '\n'.join(''.join('#' if (y >= r and((x - r) ** 2 + (
            y - r) ** 2 <= r ** 2 or (x - 3 * r) ** 2 + (y - r) ** 2 < r ** 2)
        ) or (y < r and x + r < y and x - r > 4 * r - y) else '.' for x in
            range(4 * r)) for y in range(1, 3 * r, 2)))(9) +
            "\n! ti htiw laeD ........####################........\n"[::-1])
    check_for_updates() if args.checkupdates else log.debug("No Check Updates")
    if args.tests:
        testmod(verbose=True, report=True, exclude_empty=True)
        sys.exit(0)
    log.disable(log.CRITICAL) if args.quiet else log.debug("Max Logging ON")
    log.info(__doc__ + __version__)
    check_working_folder(os.path.dirname(args.fullpath))
    if os.path.isfile(args.fullpath) and args.fullpath.endswith(".css"):
        log.info("Target is a CSS File.")  #  Work based on if argument is
        list_of_files = str(args.fullpath)  # file or folder, folder is slower.
        process_single_css_file(args.fullpath)
    elif os.path.isfile(args.fullpath) and args.fullpath.endswith(
            ".html" if args.overwrite else ".htm"):
        log.info("Target is HTML File.")
        list_of_files = str(args.fullpath)
        process_single_html_file(args.fullpath)
    elif os.path.isfile(args.fullpath) and args.fullpath.endswith(".js"):
        log.info("Target is a JS File.")
        list_of_files = str(args.fullpath)
        process_single_js_file(args.fullpath)
    elif os.path.isdir(args.fullpath):
        log.info("Target is a Folder with CSS, HTML, JS files !.")
        log.warning("Processing a whole Folder may take some time...")
        list_of_files = walkdir_to_filelist(
            args.fullpath,
            (".css", ".js", ".html" if args.overwrite else ".htm"),
            (".min.css", ".min.js", ".htm" if args.overwrite else ".html"))
        log.info('Total Maximum CPUs used: ~{} Cores.'.format(cpu_count()))
        pool = Pool(cpu_count())  # Multiprocessing Async
        pool.map_async(process_multiple_files, list_of_files)
        pool.close()
        pool.join()
    else:
        log.critical("File or folder not found,or cant be read,or I/O Error.")
        sys.exit(1)
    if only_on_py3((args.after, getoutput)):
        log.info(getoutput(str(args.after)))
    log.info('\n {0} \n Files Processed: {1}.'.format('-' * 80, list_of_files))
    log.info('Number of Files Processed: {}.'.format(
        len(list_of_files) if isinstance(list_of_files, tuple) else 1))
    make_post_execution_message()


if __name__ in '__main__':
    main()
