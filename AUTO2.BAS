' SUSKEBTIBILITEETIN AUTOMAATTINEN MITTAUS MS2E1 OHJELMALLA
' UTUSCAN-mittaradalla
' rinnakkaisportin 888 kautta ohjataan askelmoottoreita
' ja sarjaportin kautta com1 tai com2 ohjataan MS2 yksikk”„

'------------------------------------------------------------
REM askelmoottorien viiveet riippuvat tietokoneen tehosta
REM muuta viiveet jos tarpeen!!!
'------------------------------------------------------------

REM HŽTŽPYSŽYTYS
	key off
	key (1) on
	on key (1) gosub aloppu

cls
print
print:print:
PRINT "------------------------------------------------"
PRINT "         A very simple MS2 measuring program"
print "              Timo Saarinen 2004-2005"
print
print "              FOR MS2E1 SENSOR ONLY                     "
print "         AUTOMATIC MEASUREMENTS, DATA TO A FILE  "
print
print "------------------------------------------------"
print
beep
print "           Turn on the MS2 system"
print
print "          Press any key when MS2 is ON"
print ""

do  :REM Odota n„pp„inpainallusta
	a$=inkey$
	if a$<>"" then pois
wend
pois:

REM: AVAA COM1 tai COM2 portit
open "com1:1200,N,7,2,LF,PE" AS #1
'open "com2:1200,N,7,2,LF,PE" AS #1
print "                    COM:1 is running"
print "    WAIT UP TO 20 MIN UNTIL THE SYSTEM IS WARM UP"
print
print "                      ZEROING ...."
sound 300,1.5
print #1,"Z"
sound 300,1.5
delay(1.5)
cls
gosub kysy :REM tallennustiedosto ja mittausv„lit
print

MENU:
cls
print ".................................................."
print ".            Automatic MS2-system                .";:Print"   File :";tiedosto$
print ".                                                ."
print ".            Z = ZEROING/NOLLAUS                 .";:Print"   Start      :";aa
print ".            I = MEASURE AIR/ MITTAA ILMA        .";:print"   Last depth : ";vv
print ".            K = MEASURE CALIBRATION             ."
print ".            M = MEASURE SAMPLE / MITTAA NŽYTE   ."
print ".            U = NEW FILE                        ."
print ".            Q = QUIT / LOPETA OHJELMA           ."
print ".						."
print ".          A = backward until any key pressed    ."
print ".          L = forward until any key pressed     ."
print ".                                                ."
print ".                    F1 = stop                   ."
print ".................................................."
print
print
print " SELECT OPERATION "; :INPUT k$
if k$="z" or k$="Z" then print #1,"Z": GOTO MENU
if k$="i" or k$="i" then print #1,"M": input #1, A$:GOSUB TALTEENILMA:GOTO MENU
if k$="k" or k$="K" then print #1,"M": input #1,c$:gosub calib:goto menu
if k$="M" or k$="m" or k$="" then goto uusi
if k$="U" or k$="u" then close #2: gosub kysy:goto menu
if k$="Q" or k$="q" then goto loppu
if k$="A" or k$="a" then gosub alkuun:goto menu
if k$="L" or k$="l" then gosub loppuun:goto menu
goto menu

loppu:
	out 888,0 :REM sammuta moottorit
	close #2
	close #1
end

UUSI:
cls
screen 9:REM grafiikkatila
kux=10:kuy=300:REM alkupiste k„yr„lle
gx1=kux:gy1=kuy
kk=alku
'kerroin=1
lippu1=0:REM onko eka data, jolla skaalataan k„yr„„
lippu2=0
gosub xakseli: REM piirr„ x-akseli
for b=kk to vika
		gosub laske
        delay (1)
	print #1,"M": input #1,s$
		GOSUB TALTEEN
	sound 333,1.5
		gosub nosta
	delay (1.5)
	datay=0
	print #1,"M":input #1,A$
        datay=val(s$)
        datay=datay-val(a$)
	'if lippu1=0 then a=a: if datay<20 then kerroin=8 else kerroin=1:lippu1=1
		GOSUB TALTEENILMA
        datay=datay*kerroin
        if datay>300 then datay=datay-300
        gx2=gx1+hyppy:gy2=kuy-datay
	if gx2>600 then line(10,kuy)-(gx2,kuy),7:gx2=10:gx1=10:kuy=kuy :cls:gosub xakseli: rem uusi alku
	if lippu2=1 then a=a: line (gx1,gy1)-(gx2,gy2),15
        circle(gx2,gy2),2
	gx1=gx2:gy1=gy2
        kux=kux+2

	sound 500,1.0
        if hyppy=2 then qkierros=1
        if hyppy=4 then qkierros=2
        if hyppy=6 then qkierros=3
        if hyppy=8 then qkierros=4
        if hyppy=10 then qkierros=5
        	gosub monta
        lippu2=1:rem viiva vasta tokalla kerralla
        if inkey$<>"" then screen 0:goto menu
	next b
        screen 0
GOTO MENU

xakseli: REM piirret„„n akselit
	line (kux,kuy)-(kux+600,kuy),15
	for k=0 to 600 step 10
		line (kux+k,kuy-3)-(kux+k,kuy+3),15
	next k
	line (kux,kuy)-(kux,kuy-300),15
	for k=0 to 300 step 10
		line (kux-3,kuy-k)-(kux+3,kuy-k),15
	next k
return

monta:
        m=qkierros
        for p=1 to m
                gosub kierrostaakse
	next p
return

TALTEEN:
	print #2,using "#####.###";alku;
	print #2,"  ,  ";
	print #2,s$;
	print #2," , ";
	ALKU=ALKU+hyppy
return

TALTEENILMA:
	PRINT #2, "AIR ,";
	print #2,a$
RETURN

calib:
	print #2,"LAST CALIB :";c$,
	print #2,"AT DEPTH :",ALKU
return


kysy:
	print
	PRINT "  Give the filename max 8 ch ";: INPUT TIEDOSTO$
	PRINT "  Give starting depth (mm) ";:INPUT alku
	aa=alku
	PRINT "  Give last measurement depth (mm) ";:INPUT vika
	vv=vika
	PRINT "  Give measurement interval (2 or 4 or 6 or 8 or 10 mm) ";:input hyppy
	vika=int(vika/hyppy)
	open "O",#2,tiedosto$
        PRINT "  Give range 1= (short measurement) 2 (long measurement)";
        input kerro$
        if kerro$="1" then kerroin=10 else kerroin=1
return

REM ASKELMOOTTORIEN OHJAUS PORTIN 888 (LPT1) kautta

kierroseteen: REM 2 mm per sarja
        for k=1 to 67
		out 888,1
		gosub viive2
		out 888,4
		gosub viive2
		out 888,2
		gosub viive2
		out 888,8
		gosub viive2
	next k
out 888,0
y=y+2
return

kierrostaakse: REM 2 mm per sarja
        gosub viive2
	for k=1 to 67
		out 888,2 REM askelmoottoreille 4 per„kk„ist„ signaalia
		gosub viive2
		out 888,4
		gosub viive2
		out 888,1
		gosub viive2
		out 888,8
		gosub viive2
	next k
out 888,0
y=y+2
return

REM VIIVEET TIETOKONEKOHTAISIA MUUTA JOS NOPEAMPI KONE
viive:
	for a=1 to 550:next
return

viive2:
	for a=1 to 200:next
return

viive3:
	for a=1 to 2000:next
return

nosta:  REM nopea nosto
	for k=1 to 25
		out 888,16
		gosub viive
		out 888,64
		gosub viive
		out 888,32
		gosub viive
		out 888,128
		gosub viive
        out 888,0
next k
out 888,0
return

laske:
	for k=1 to 10  :REM aluksi nopeasti
		out 888,16
		gosub viive
		out 888,64
		gosub viive
		out 888,32
		gosub viive
		out 888,128
		gosub viive
	out 888,0
	next k
	for k=1 to 15  :REM sitten hitaasti
		out 888,16
		gosub viive3
		out 888,64
		gosub viive3
		out 888,32
		gosub viive3
		out 888,128
		gosub viive3
	out 888,0
        next k
        out 888,0
return

aloppu:
	out 888,0
        screen 0
        print:print
	print "    Motors OFF"
	close #1
	print "    Com-port closed"
	close #2
        print "    File closed"
	end
return

alkuun:  REM py”ritet„„  kunnes key pressed
        do
		gosub kierroseteen
        loop until instat
return

loppuun:  REM py”ritet„„n kunnes key pressed
	do
		gosub kierrostaakse
        loop until instat
return

' Timo Saarisen ikioma suskiksen automaattinen mittausohjelma
' 17-19.5.2005
' Laitten rakensivat Lasse Lehtinen (elektroniikka) ja Kari Kurukorpi (mekaniikka)
' Ohjelma piirt„„ yksinkertaisen k„yr„n mitatessa
' jos x yli 600 niin takaisin alkuun
' jos y yli 300 niin y=y-300
' jos herkkyys 0.1 niin 1 piste=1 suskislukema jos 1.0 niin 1 piste=10
' ohjelma toimii hienosti...
