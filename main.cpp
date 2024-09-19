#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <fstream>
#include <sstream>
#include <vector>

class GraphWindow : public Gtk::Window {
public:
    GraphWindow() {
        set_default_size(800, 600);
        signal_draw().connect(sigc::mem_fun(*this, &GraphWindow::on_draw));
        load_data();
    }

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
        cr->set_line_width(2.0);

        // Dibujar gráfico del mejor caso
        cr->set_source_rgb(0.0, 0.0, 1.0); // Azul
        draw_graph(cr, best_case_times);

        // Dibujar gráfico del peor caso
        cr->set_source_rgb(1.0, 0.0, 0.0); // Rojo
        draw_graph(cr, worst_case_times);

        // Dibujar gráfico del caso promedio
        cr->set_source_rgb(0.0, 1.0, 0.0); // Verde
        draw_graph(cr, average_case_times);

        return true;
    }

private:
    void load_data() {
        std::ifstream file("bubble_sort_performance.csv");
        std::string line;
        std::getline(file, line); // Saltar encabezado

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string size_str, best_case_str, worst_case_str, average_case_str;
            std::getline(ss, size_str, ',');
            std::getline(ss, best_case_str, ',');
            std::getline(ss, worst_case_str, ',');
            std::getline(ss, average_case_str, ',');

            sizes.push_back(std::stod(size_str));
            best_case_times.push_back(std::stod(best_case_str));
            worst_case_times.push_back(std::stod(worst_case_str));
            average_case_times.push_back(std::stod(average_case_str));
        }
    }

    void draw_graph(const Cairo::RefPtr<Cairo::Context>& cr, const std::vector<double>& times) {
        double x_scale = get_width() / sizes.back();
        double y_scale = get_height() / (*std::max_element(times.begin(), times.end()));

        for (size_t i = 0; i < sizes.size(); ++i) {
            double x = sizes[i] * x_scale;
            double y = get_height() - (times[i] * y_scale);
            cr->line_to(x, y);
        }

        cr->stroke();
    }

    std::vector<double> sizes;
    std::vector<double> best_case_times;
    std::vector<double> worst_case_times;
    std::vector<double> average_case_times;
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "com.example.graph");
    GraphWindow window;
    return app->run(window);
}
