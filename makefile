all: main.c
	gcc -Ilibs/ -xc main.c -xc engine/object.c -xc game/gameobject.c libs/elboronlib.c libs/prometheusgamelib.c engine/shader.c engine/camera.c engine/gamewindow.c -std=c99 -o Barbaria -lGL -lGLEW -lglfw -ldl -lX11 -lpthread -lXrandr -lXi -lm
