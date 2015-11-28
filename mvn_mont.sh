java -cp MLR.jar montador.MvnAsm asdf.asm
java -cp MLR.jar relocator.MvnRelocator asdf.mvn 0000 000
java -Dfile.encoding=cp850 -jar mvn.jar
