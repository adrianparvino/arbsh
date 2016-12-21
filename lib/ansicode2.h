setnl LMN             Set new line mode                      "\033[[20h"
setappl DECCKM        Set cursor key to application          "\033[[?1h"
setansi DECANM        Set ANSI (versus VT52)                 none
setcol DECCOLM        Set number of columns to 132           "\033[[?3h"
setsmooth DECSCLM     Set smooth scrolling                   "\033[[?4h"
setrevscrn DECSCNM    Set reverse video on screen            "\033[[?5h"
setorgrel DECOM       Set origin to relative                 "\033[[?6h"
setwrap DECAWM        Set auto-wrap mode                     "\033[[?7h"
setrep DECARM         Set auto-repeat mode                   "\033[[?8h"
setinter DECINLM      Set interlacing mode                   "\033[[?9h"

setlf LMN             Set line feed mode                     "\033[[20l"
setcursor DECCKM      Set cursor key to cursor               "\033[[?1l"
setvt52 DECANM        Set VT52 (versus ANSI)                 "\033[[?2l"
resetcol DECCOLM      Set number of columns to 80            "\033[[?3l"
setjump DECSCLM       Set jump scrolling                     "\033[[?4l"
setnormscrn DECSCNM   Set normal video on screen             "\033[[?5l"
setorgabs DECOM       Set origin to absolute                 "\033[[?6l"
resetwrap DECAWM      Reset auto-wrap mode                   "\033[[?7l"
resetrep DECARM       Reset auto-repeat mode                 "\033[[?8l"
resetinter DECINLM    Reset interlacing mode                 "\033[[?9l"

altkeypad DECKPAM     Set alternate keypad mode              "\033[="
numkeypad DECKPNM     Set numeric keypad mode                "\033[>"

setukg0               Set United Kingdom G0 character set    "\033[(A"
setukg1               Set United Kingdom G1 character set    ""\033[)A"
setusg0               Set United States G0 character set     "\033[(B"
setusg1               Set United States G1 character set     "\033[)B"
setspecg0             Set G0 special chars. & line set       "\033[(0"
setspecg1             Set G1 special chars. & line set       "\033[)0"
setaltg0              Set G0 alternate character ROM         \033[(1"
setaltg1              Set G1 alternate character ROM         "\033[)1"
setaltspecg0          Set G0 alt char ROM and spec. graphics "\033[(2"
setaltspecg1          Set G1 alt char ROM and spec. graphics "\033[)2"

setss2 SS2            Set single shift 2                     "\033[N"
setss3 SS3            Set single shift 3                     "\033[O"

modesoff SGR0         Turn off character attributes          "\033[[m"
modesoff SGR0         Turn off character attributes          "\033[[0m"
bold SGR1             Turn bold mode on                      "\033[[1m"
lowint SGR2           Turn low intensity mode on             "\033[[2m"
underline SGR4        Turn underline mode on                 "\033[[4m"
blink SGR5            Turn blinking mode on                  "\033[[5m"
reverse SGR7          Turn reverse video on                  "\033[[7m"
invisible SGR8        Turn invisible text mode on            "\033[[8m"

setwin DECSTBM        Set top and bottom line#s of a window  "\033[[<v>;<v>r"

cursorup(n) CUU       Move cursor up n lines                 "\033[[<n>A"
cursordn(n) CUD       Move cursor down n lines               "\033[[<n>B"
cursorrt(n) CUF       Move cursor right n lines              "\033[[<n>C"
cursorlf(n) CUB       Move cursor left n lines               "\033[[<n>D"
cursorhome            Move cursor to upper left corner       "\033[[H"
cursorhome            Move cursor to upper left corner       "\033[[;H"
cursorpos(v,h) CUP    Move cursor to screen location v,h     "\033[[<v>;<h>H"
hvhome                Move cursor to upper left corner       "\033[[f"
hvhome                Move cursor to upper left corner       "\033[[;f"
hvpos(v,h) CUP        Move cursor to screen location v,h     "\033[[<v>;<h>f"
index IND             Move/scroll window up one line         "\033[D"
revindex RI           Move/scroll window down one line       "\033[M"
nextline NEL          Move to next line                      "\033[E"
savecursor DECSC      Save cursor position and attributes    "\033[7"
restorecursor DECSC   Restore cursor position and attributes "\033[8""
"
tabset HTS            Set a tab at the current column        "\033[H"
tabclr TBC            Clear a tab at the current column      "\033[[g"
tabclr TBC            Clear a tab at the current column      "\033[[0g"
tabclrall TBC         Clear all tabs                         "\033[[3g"

dhtop DECDHL          Double-height letters, top half        "\033[#3"
dhbot DECDHL          Double-height letters, bottom half     "\033[#4"
swsh DECSWL           Single width, single height letters    "\033[#5"
dwsh DECDWL           Double width, single height letters    "\033[#6"

cleareol EL0          Clear line from cursor right           "\033[[K"
cleareol EL0          Clear line from cursor right           "\033[[0K"
clearbol EL1          Clear line from cursor left            "\033[[1K"
clearline EL2         Clear entire line                      "\033[[2K"

cleareos ED0          Clear screen from cursor down          \033[[J
cleareos ED0          Clear screen from cursor down          \033[[0J
clearbos ED1          Clear screen from cursor up            \033[[1J
clearscreen ED2       Clear entire screen                    \033[[2J

devstat DSR           Device status report                   \033[5n
termok DSR               Response: terminal is OK            \033[0n
termnok DSR              Response: terminal is not OK        \033[3n

getcursor DSR         Get cursor position                    \033[6n
cursorpos CPR            Response: cursor is at v,h          \033[<v>;<h>R

ident DA              Identify what terminal type            \033[[c
ident DA              Identify what terminal type (another)  \033[[0c
gettype DA               Response: terminal type code n      \033[[?1;<n>0c

reset RIS             Reset terminal to initial state        \033[c

align DECALN          Screen alignment display               \033[#8
testpu DECTST         Confidence power up test               \033[[2;1y
testlb DECTST         Confidence loopback test               \033[[2;2y
testpurep DECTST      Repeat power up test                   \033[[2;9y
testlbrep DECTST      Repeat loopback test                   \033[[2;10y

ledsoff DECLL0        Turn off all four leds                 \033[[0q
led1 DECLL1           Turn on LED #1                         \033[[1q
led2 DECLL2           Turn on LED #2                         \033[[2q
led3 DECLL3           Turn on LED #3                         \033[[3q
led4 DECLL4           Turn on LED #4                         \033[[4q

/*
 All codes below are for use in VT52 compatibility mode.
*/


setansi               Enter/exit ANSI mode (VT52)            \033[<

altkeypad             Enter alternate keypad mode            \033[=
numkeypad             Exit alternate keypad mode             \033[>

setgr                 Use special graphics character set     \033[F
resetgr               Use normal US/UK character set         \033[G

cursorup              Move cursor up one line                \033[A
cursordn              Move cursor down one line              \033[B
cursorrt              Move cursor right one char             \033[C
cursorlf              Move cursor left one char              \033[D
cursorhome            Move cursor to upper left corner       \033[H
cursorpos(v,h)        Move cursor to v,h location            \033[<v><h>
revindex              Generate a reverse line-feed           \033[I

cleareol              Erase to end of current line           \033[K
cleareos              Erase to end of screen                 \033[J

ident                 Identify what the terminal is          \033[Z
identresp             Correct response to ident              \033[/Z

