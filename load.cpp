// gcc expose.c -o expose `pkg-config gtk+-3.0 --cflags --libs`
#include <gtk/gtk.h>
#include <stdlib.h>

GdkPixbuf *pix[5];
struct timespec tim;

unsigned int image=0,d=0;

cairo_t *cr;

static gboolean keypress (GtkWidget *da, GdkEvent *event, gpointer data)
{
	printf("%d nanoseconds\n",tim.tv_nsec);
	tim.tv_nsec+=100000000L;
	d++;
	if(d>3)exit(1);
	
}

static gboolean on_window_draw (GtkWidget *da, GdkEvent *event, gpointer data)
{
    (void)event; (void)data;
    GError *err = NULL;
    nanosleep((const struct timespec*)&tim, NULL);
    /* Create pixbuf */
    if(err)
    {
        printf("Error : %s\n", err->message);
        g_error_free(err);
        return FALSE;
    }
    //    cr = gdk_cairo_create (da->window);

    cairo_t *cr;
    cr = gdk_cairo_create (gtk_widget_get_window(da));
    //    cr = gdk_cairo_create (da->window);
    gdk_cairo_set_source_pixbuf(cr, pix[image++], 0, 0);
    if(image>4)image=0;
    cairo_paint(cr);
    //    cairo_fill (cr);
    cairo_destroy (cr);
    if (tim.tv_nsec>1)tim.tv_nsec-=tim.tv_nsec*.01;
  
	gtk_widget_queue_draw(da);
  
}

int main ( int argc, char **argv) {
    GtkWidget *window;
    GtkWidget *canvas;
    GError *err = NULL;
	tim.tv_sec = 0;
	tim.tv_nsec = 500000000L;
    gtk_init (&argc , &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (window,
        200, 325);
    pix[0] = gdk_pixbuf_new_from_file("star.png", &err);
    pix[1] = gdk_pixbuf_new_from_file("waves.png", &err);
    pix[2] = gdk_pixbuf_new_from_file("circle.png", &err);
    pix[3] = gdk_pixbuf_new_from_file("square.png", &err);
    pix[4] = gdk_pixbuf_new_from_file("plus.png", &err);

    g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit) , NULL);
  g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (keypress), NULL);
      canvas = gtk_drawing_area_new ();
    gtk_container_add (GTK_CONTAINER (window), canvas);
    g_signal_connect (canvas, "draw", (GCallback) on_window_draw, NULL);

    gtk_widget_set_app_paintable(canvas, TRUE);
    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}
