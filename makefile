# Jingxin Zhang

all:  tags headers lab4 lab4u p1 p2 p3 p4

headers: *.c tags
	headers.sh

tags: *.c
	ctags -R .

lab4: lab4.o bits.o output.o input.o physics.o memory.o callback.o list.o reliable.o
	gcc -g -o $@ $^ -L. -langry -lncurses -lm

lab4u: lab4.o bits.o output.o input.o physics.o memory.o callback.o list.o unreliable.o
	gcc -g -o $@ $^ -L. -langry -lncurses -lm

# prototype that is not running
p1: p1.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -langry -lncurses -lm

# prototype that tests iterate
p2: p2.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -langry -llinkedlist -lncurses -lm

# prototype that tests deleteSome
p3: p3.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -langry -llinkedlist -lncurses -lm

# prototype that tests how insert and sort
p4: p4.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -langry -llinkedlist -lncurses -lm

# prototype that tests openFile
p5: p5.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -langry -llinkedlist -lncurses -lm

# this is our master compiler rule to generate .o files.
# It needs all 4 warnings

#rules to build lab4.zip
lab4.zip: makefile *.c *.h *.a README_LAB4 reliable.o unreliable.o
	#the dependency of the current rule
	zip $@ $^
	#first remove old install folder
	rm -rf install
	#create the install folder
	mkdir install
	#unzip to the install folder
	unzip lab4.zip -d install
	#make the lab4 target
	make -C install -r lab4


%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@



