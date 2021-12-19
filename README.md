# bmp-file-parser
**usage:**
compile it -> `./program PATH-TO-INPUT-BMP-FILE PATH-TO-OUTPUT-BMP-FILE`<br>
or<br>
`./program PATH-TO-INPUT-BMP-FILE`<br>

**functionality:**
the program prints out `FileHeader`, `InfoHeader` and `RGB histogram` of the input file.<br>
if path to output is stated, it converts input file to grayscale bmp image.<br>

**requirements:**<br>
Compression == 0<br>
BitCount != 24