# CMSC 15200 Project 2

.PHONY: clean

p36: project2.h project2-utils.c p36.c
	clang -Wall -o p36 project2-utils.c p36.c -lm

p63: project2.h project2-utils.c p63.c
	clang -Wall -o p63 project2-utils.c p63.c -lm

pz3: project2.h project2-utils.c pz3.c
	clang -Wall -o pz3 project2-utils.c pz3.c -lm

p3z: project2.h project2-utils.c p3z.c
	clang -Wall -o p3z project2-utils.c p3z.c -lm

pzg: project2.h project2-utils.c pzg.c
	clang -Wall -o pzg project2-utils.c pzg.c -lm

pzh: project2.h project2-utils.c pzh.c
	clang -Wall -o pzh project2-utils.c pzh.c -lm

pzm: project2.h project2-utils.c pzm.c
	clang -Wall -o pzm project2-utils.c pzm.c -lm

pzn: project2.h project2-utils.c pzn.c
	clang -Wall -o pzn project2-utils.c pzn.c -lm

pzw: project2.h project2-utils.c pzw.c
	clang -Wall -o pzw project2-utils.c pzw.c -lm

# These targets include -g for debugging.

dp36: project2.h project2-utils.c p36.c
	clang -g -Wall -o p36 project2-utils.c p36.c -lm

dp63: project2.h project2-utils.c p63.c
	clang -g -Wall -o p63 project2-utils.c p63.c -lm

dpz3: project2.h project2-utils.c pz3.c
	clang -g -Wall -o pz3 project2-utils.c pz3.c -lm

dp3z: project2.h project2-utils.c p3z.c
	clang -g -Wall -o p3z project2-utils.c p3z.c -lm

dpzg: project2.h project2-utils.c pzg.c
	clang -g -Wall -o pzg project2-utils.c pzg.c -lm

dpzh: project2.h project2-utils.c pzh.c
	clang -g -Wall -o pzh project2-utils.c pzh.c -lm

dpzm: project2.h project2-utils.c pzm.c
	clang -g -Wall -o pzm project2-utils.c pzm.c -lm

dpzn: project2.h project2-utils.c pzn.c
	clang -g -Wall -o pzn project2-utils.c pzn.c -lm

dpzw: project2.h project2-utils.c pzw.c
	clang -g -Wall -o pzw project2-utils.c pzw.c -lm

# Type "make push" to run three git phases.

push:
	git add *.h *.c && git commit -m 'proj2 via make' && git push

# Remove executables and debugging info (in *dSYM directories).

clean:
	rm -rf p36 p63 pz3 p3z pzg pzh pzm pzn pzw a.out *.dSYM
