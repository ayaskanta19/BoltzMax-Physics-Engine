override CXX := C:\Users\AshKiller47\Documents\MinGW\bin\g++.exe

all: engine examples

engine: compile_engine move_engine

examples: compile_examples move_examples link_examples

clean: clean_engine clean_examples

compile_engine:
	$(CXX) -std=c++17 -c src\BoltzMax\Physics\\*.cpp -Iinclude

compile_examples:
	FOR %%A IN ("examples\*.cpp") DO ($(CXX) -std=c++17 -c %%A -IC:\Retrofit\Libraries\SFML-2.6.1\include -Iinclude -DSFML_STATIC)

move_engine:
	move /Y "*.o" obj\engine

move_examples:
	move /Y "*.o" obj\examples

link_examples:
	FOR %%A IN ("obj\examples\*.o") DO ($(CXX) -static %%A obj\engine\\*.o -o bin\%%~nA -LC:\Retrofit\Libraries\SFML-2.6.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main)

clean_engine:
	del obj\engine\\*.o

clean_examples:
	del obj\examples\\*.o bin\\*.exe