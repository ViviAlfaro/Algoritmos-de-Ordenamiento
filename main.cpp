#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

class GraphWindow : public Gtk::Window {
public:
    GraphWindow() {
        set_default_size(800, 600);
        set_title("Performance Graphs");
        signal_draw().connect(sigc::mem_fun(*this, &GraphWindow::on_draw));
        load_data("bubble_sort_performance.csv", bubble_best, bubble_worst, bubble_average);
        load_data("selection_sort_performance.csv", selection_best, selection_worst, selection_average);
        load_data("merge_sort_performance.csv", merge_best, merge_worst, merge_average);
        load_data("binary_search_tree_performance.csv", bst_best, bst_worst, bst_average);
        load_data("sorted_linked_list_performance.csv", sorted_linked_list_best, sorted_linked_list_worst, sorted_linked_list_average);
    }

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
        cr->set_line_width(2.0);

        // Draw Bubble Sort Graph
        draw_graph(cr, bubble_sizes, bubble_best, "Bubble Sort - Best Case", 0.0, 0.0, 1.0);
        draw_graph(cr, bubble_sizes, bubble_worst, "Bubble Sort - Worst Case", 1.0, 0.0, 0.0);
        draw_graph(cr, bubble_sizes, bubble_average, "Bubble Sort - Average Case", 0.0, 1.0, 0.0);

        // Draw other graphs similarly
        // ...

        return true;
    }

private:
    void load_data(const std::string& filename, std::vector<double>& best_case, std::vector<double>& worst_case, std::vector<double>& average_case) {
        std::ifstream file(filename);
        std::string line;
        std::getline(file, line); // Skip header line

        std::vector<double> sizes;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string size_str, best_case_str, worst_case_str, average_case_str;
            std::getline(ss, size_str, ',');
            std::getline(ss, best_case_str, ',');
            std::getline(ss, worst_case_str, ',');
            std::getline(ss, average_case_str, ',');

            sizes.push_back(std::stod(size_str));
            best_case.push_back(std::stod(best_case_str));
            worst_case.push_back(std::stod(worst_case_str));
            average_case.push_back(std::stod(average_case_str));
        }
    }

    void draw_graph(const Cairo::RefPtr<Cairo::Context>& cr, const std::vector<double>& sizes, const std::vector<double>& times, const std::string& title, double r, double g, double b) {
        if (sizes.empty() || times.empty()) return;

        cr->set_source_rgb(r, g, b);
        cr->set_line_width(2.0);

        double x_scale = get_width() / sizes.back();
        double y_scale = get_height() / (*std::max_element(times.begin(), times.end()));

        cr->move_to(sizes[0] * x_scale, get_height() - (times[0] * y_scale));
        for (size_t i = 1; i < sizes.size(); ++i) {
            cr->line_to(sizes[i] * x_scale, get_height() - (times[i] * y_scale));
        }
        cr->stroke();
        
        // Draw title
        cr->move_to(10, 20);
        cr->set_source_rgb(0.0, 0.0, 0.0); // Black
        cr->show_text(title);
    }

    // Data storage for multiple algorithms
    std::vector<double> bubble_sizes, bubble_best, bubble_worst, bubble_average;
    std::vector<double> selection_best, selection_worst, selection_average;
    std::vector<double> merge_best, merge_worst, merge_average;
    std::vector<double> bst_best, bst_worst, bst_average;
    std::vector<double> sorted_linked_list_best, sorted_linked_list_worst, sorted_linked_list_average;
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "com.example.graph");
    GraphWindow window;
    return app->run(window);
}
