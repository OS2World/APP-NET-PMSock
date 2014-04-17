/* Make so32dll.a and tcp32dll.a from .dlls 

  IBM's TCP .dlls define each funtion twice, so we'll just duplicate
   each line of the output from EMXIMP 

  requires: IMPLIB - to create .lib from .dll
	      EMXIMP - to create .imp from .lib, and .a from .imp
*/             
/* parameters: socklib <tcpdir> <lib>*/
arg tcpdir lib

/* make initial lib file, note: it can't be used for linking */
say "Creating LIB file.."
'@implib 'lib'.lib 'tcpdir'\dll\'lib'.dll>nul'

/* convert from lib to def format */
say "Creating IMP file.."
'@emximp -o 'lib'.imp 'lib'.lib'
'@if exist 'lib'.tmp del 'lib'.tmp>nul'
'@rename 'lib'.imp 'lib'.tmp>nul'

say "Parsing IMP file.."
/* parse imp file, duplicating lines to lowercase */
file=lib'.tmp'
impfile=lib'.imp'

'@if exist 'impfile' del 'impfile'>nul'

line=linein(file)
do while left(line,1)=';'
  call lineout impfile, line 
  line=linein(file)
end 
do while lines(file)<>0
  call lineout impfile, line
  call lineout impfile, translate(line, 'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')
  line=linein(file)
end
/* convert .imp to .a for use in linking */

say "Creating library.."
'@emximp -o 'lib'.a 'lib'.imp'

/* cleanup tmp & invalid files */
say "Done!"
