10 rem 1200,8n1
20 print "{clear}{white}"
30 open2,2,4,chr$(8)+chr$(0):rem open the serial from user port
40 get#2,s$:rem get from serial to prime the pump
100 rem main loop
110 rem ---------
200 get k$:rem get from c64 keyboard
220 if k$<>""then print#2,k$;:rem send keypress to serial
230 get#2,s$:rem get byte from serial
240 print s$;k$;:rem print these bytes
245 if (peek(673)and1)then 245:rem wait until all chars transmitted
900 goto 110
1000 close 2:end