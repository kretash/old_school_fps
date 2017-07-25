g++ -std=c++14 -I/usr/local/include -L/usr/local/lib -I../include/  -lSDL2 -lglew -framework OpenGL -o ../build/program.out ../src/main.cc ../src/renderer.cc ../src/gl_renderer.cc -DBACK_ASSETS_PATH
