gcc -Wall -g load.cpp -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -I /usr/include/cairo -I /usr/include/gtk-3.0 -I /usr/include/glib-2.0 -I /usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/lib64/gtk-3.0/include -I /usr/include/pango-1.0  -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0 -o load


Start the program.
When you lose focus on the symbols push a key.
the program will print the time between frames in nanoseconds.
when you push a key 4 times the program will exit.
