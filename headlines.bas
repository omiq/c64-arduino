10 rem 1200,8n1
20 print "{clear}{white}"
30 open2,2,4,chr$(8)+chr$(0):rem open the serial from user port
40 get#2,s$:rem get from serial to prime the pump
100 rem main loop
110 rem ---------
120 get#2,s$:rem get byte from serial
130 if s$="[" then print chr$(13)+"{white}{reverse on}";: goto 200
140 if s$="]" then print "{reverse off}{light blue}"+chr$(13);: goto 200
150 print s$;:rem print bytes
200 if (peek(673)and1)then 200: rem wait until all chars transmitted
900 goto 120
1000 close 2:end