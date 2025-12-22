#include <gtk/gtk.h>
#include <stdio.h>

// Bu fonksiyon butona tıklandığında çalışır
static void on_theme_button_clicked(GtkWidget *widget, gpointer script_path) {
    GError *error = NULL;
    const char *command = (const char *)script_path;

    g_print("Çalıştırılıyor: %s\n", command);

    // Scripti arka planda çalıştır (Arayüz donmaz)
    // Bu fonksiyon shell komutu gibi çalışır, scriptin yolunu tam ver
    if (!g_spawn_command_line_async(command, &error)) {
        g_printerr("Hata oluştu: %s\n", error->message);
        g_error_free(error);
    } else {
        // İsteğe bağlı: Başarılı olursa kullanıcıya bir bildirim (notify-send) de gönderebilirsin
        // g_spawn_command_line_async("notify-send 'Tema Değiştirildi'", NULL);
    }
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *label;
    
    // --- PENCERE AYARLARI ---
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hyprland Tema Seçici");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 250);

    // Dikey kutu (VBox) oluştur
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(box, 30);
    gtk_widget_set_margin_bottom(box, 30);
    gtk_widget_set_margin_start(box, 30);
    gtk_widget_set_margin_end(box, 30);
    gtk_window_set_child(GTK_WINDOW(window), box);

    // Başlık etiketi
    label = gtk_label_new("Mevcut Temalar");
    // Yazıyı biraz büyütelim ve kalın yapalım (Pango markup)
    gtk_label_set_markup(GTK_LABEL(label), "<b><span size='large'>Tema Seçiniz</span></b>");
    gtk_box_append(GTK_BOX(box), label);

    // --- BUTON 1: TEMA A ---
    GtkWidget *btn1 = gtk_button_new_with_label("Karanlık Tema (Dark)");
    // Script yolunu buraya yazıyorsun 👇
    char *script1 = "/home/kullaniciadi/scripts/dark_theme.sh"; 
    g_signal_connect(btn1, "clicked", G_CALLBACK(on_theme_button_clicked), script1);
    gtk_box_append(GTK_BOX(box), btn1);

    // --- BUTON 2: TEMA B ---
    GtkWidget *btn2 = gtk_button_new_with_label("Aydınlık Tema (Light)");
    // Script yolunu buraya yazıyorsun 👇
    char *script2 = "/home/kullaniciadi/scripts/light_theme.sh";
    g_signal_connect(btn2, "clicked", G_CALLBACK(on_theme_button_clicked), script2);
    gtk_box_append(GTK_BOX(box), btn2);

    // --- BUTON 3: Cyberpunk ---
    GtkWidget *btn3 = gtk_button_new_with_label("Cyberpunk Tema");
    // Script yolunu buraya yazıyorsun 👇
    char *script3 = "/home/kullaniciadi/scripts/cyberpunk.sh";
    g_signal_connect(btn3, "clicked", G_CALLBACK(on_theme_button_clicked), script3);
    gtk_box_append(GTK_BOX(box), btn3);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.hyprland.themechanger", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
