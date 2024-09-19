
#include <iostream>
#include <string>
#include <getopt.h>
#include <vector>
#include <deque>
using namespace std;


template <typename T>
class Array {
    private:
    uint32_t size; 
    vector<vector<T>> Map;
    public:
    Array(); 
    Array(uint32_t var): size(var){
        Map.resize(size, vector<T>(size, 0));
    };
    
    uint32_t get_value(uint32_t rownum, uint32_t colnum) {
        return Map[rownum][colnum];
    }

    void MapChange(uint32_t rownum, uint32_t colnum, uint32_t val){
        Map[rownum][colnum] = val;
    }

    uint32_t size_returner(){
        return size; 
    }
    uint32_t area_returner(){
        return size*size;
    }
    
};



template <typename T>
class Coordinate {
    private:
    uint32_t level1;
    uint32_t row;
    uint32_t column;

    public:
    Coordinate() : level1(0), row(0), column(0) {}
    Coordinate(uint32_t number, uint32_t number2, uint32_t number3) : level1(number), row(number2), 
    column(number3) {}
 
    uint32_t get_row() {
        return row;
    }
    uint32_t get_column() {
        return column;
    }
    uint32_t get_level() {
        return level1;
    }
    void changer(uint32_t n, uint32_t o, uint32_t p){
        level1 = n; 
        row = o;
        column = p; 
    }
};

class Router {
    private:
    bool sorq; // true if stack, false if queue 
    deque<Coordinate<uint32_t>> coordinate_holder;
    Coordinate<uint32_t> current;
    vector<Array<uint32_t>> FullMap;
    vector<char> path;
    uint32_t upper_bound = 0;
    uint32_t lower_bound;
    uint32_t left_bound = 0;
    uint32_t right_bound;
    uint32_t number; 
    uint32_t full; 
    uint32_t size;
    size_t complete_index;
    uint32_t starting_number; 
    bool hangar_found = false;
    Coordinate<uint32_t> starting;
    Coordinate<uint32_t> discover;
    public:
    Router(bool method, vector<Array<uint32_t>> French, Coordinate<uint32_t> start): sorq(method), FullMap(French), starting(start) {
        coordinate_holder.push_back(starting);
        right_bound = FullMap[0].size_returner();
        lower_bound = FullMap[0].size_returner();
        full = FullMap[0].area_returner();
        size = FullMap[0].size_returner();
        complete_index = full * FullMap.size();
        path.resize(complete_index, '.');
        execute();
    };
    void push(Coordinate<uint32_t> coord){
        coordinate_holder.push_back(coord);
    }
    void execute() {
        if(sorq){
            current = coordinate_holder.back();
            coordinate_holder.pop_back();
        } else {
            current = coordinate_holder.front();
            coordinate_holder.pop_front();
        }
    }

    bool is_hangar_found(){
        if(hangar_found){
            return true;
        } else {
            return false; 
        }
    }


    void routing_process(){ 
        number = current.get_level() * full + current.get_row() * size + current.get_column(); 
        if(current.get_row() < upper_bound && FullMap[current.get_level()].get_value(current.get_row(), current.get_column()) != 4
        && FullMap[current.get_level()].get_value(current.get_row() - 1, current.get_column()) != 5
        && FullMap[current.get_level()].get_value(current.get_row() - 1, current.get_column()) != 3
        && FullMap[current.get_level()].get_value(current.get_row() - 1, current.get_column()) != 0
        && FullMap[current.get_level()].get_value(current.get_row() - 1, current.get_column()) != 4){
            if(FullMap[current.get_level()].get_value(current.get_row() - 1, current.get_column()) == 1){
                discover = Coordinate<uint32_t>(current.get_level(), current.get_row() - 1, current.get_column());
                coordinate_holder.push_back(discover);
                FullMap[current.get_level()].MapChange(current.get_row() - 1, current.get_column(), 3);
            }
            if(FullMap[current.get_level()].get_value(current.get_row() - 1, current.get_column()) == 2){
                discover = Coordinate<uint32_t>(current.get_level(), current.get_row() - 1, current.get_column());
                coordinate_holder.push_back(discover);
                FullMap[current.get_level()].MapChange(current.get_row() - 1, current.get_column(), 4);
            }
            if(FullMap[current.get_level()].get_value(current.get_row() - 1, current.get_column()) == 6){
                hangar_found = true; 
            }
           number = number - size;
            path[number] = 'n';
            if(!hangar_found){
                 number = number + size;
            }
           
        } // north, not elevator 

        
        if(current.get_column() < right_bound && 
        FullMap[current.get_level()].get_value(current.get_row(), current.get_column() + 1) != 5
        && FullMap[current.get_level()].get_value(current.get_row(), current.get_column() + 1) != 4
        && FullMap[current.get_level()].get_value(current.get_row(), current.get_column() + 1) != 3
         && FullMap[current.get_level()].get_value(current.get_row(), current.get_column() + 1) != 0){
            if(FullMap[current.get_level()].get_value(current.get_row(), current.get_column() + 1) == 1){
                discover = Coordinate<uint32_t>(current.get_level(), current.get_row(), current.get_column() + 1);
                coordinate_holder.push_back(discover);
                FullMap[current.get_level()].MapChange(current.get_row(), current.get_column() + 1, 3);
            }
            if(FullMap[current.get_level()].get_value(current.get_row(), current.get_column() + 1) == 2){
                discover = Coordinate<uint32_t>(current.get_level(), current.get_row(), current.get_column() + 1);
                coordinate_holder.push_back(discover);
                FullMap[current.get_level()].MapChange(current.get_row(), current.get_column() + 1, 4);
            }
            if(FullMap[current.get_level()].get_value(current.get_row(), current.get_column() + 1) == 6){
                hangar_found = true; 
            }
            number = number + 1;
            path[number] = 'e';
            if(hangar_found){
                number = number - 1;
            }
            
           
        } // east, not elevator 
        
        if(current.get_row() > lower_bound && FullMap[current.get_level()].get_value(current.get_row(), current.get_column()) != 4
        && FullMap[current.get_level()].get_value(current.get_row() + 1, current.get_column()) != 5
        && FullMap[current.get_level()].get_value(current.get_row() + 1, current.get_column()) != 4
        && FullMap[current.get_level()].get_value(current.get_row() + 1, current.get_column()) != 3
        && FullMap[current.get_level()].get_value(current.get_row() + 1, current.get_column()) != 0){
            if(FullMap[current.get_level()].get_value(current.get_row() + 1, current.get_column()) == 1){
                discover = Coordinate<uint32_t>(current.get_level(), current.get_row() + 1, current.get_column());
                coordinate_holder.push_back(discover);
                FullMap[current.get_level()].MapChange(current.get_row() + 1, current.get_column(), 3);
            }
            if(FullMap[current.get_level()].get_value(current.get_row() + 1, current.get_column()) == 2){
                discover = Coordinate<uint32_t>(current.get_level(), current.get_row() + 1, current.get_column());
                coordinate_holder.push_back(discover);
                FullMap[current.get_level()].MapChange(current.get_row() + 1, current.get_column(), 4);
            }
            if(FullMap[current.get_level()].get_value(current.get_row() + 1, current.get_column()) == 6){
                hangar_found = true; 
            }
            number = number + size;
            path[number] = 's';
            if(!hangar_found){
               number = number + size; 
            }
            
    
        } // south, not elevator 



        if(current.get_column() > left_bound 
        && FullMap[current.get_level()].get_value(current.get_row(), current.get_column() - 1) != 5
        && FullMap[current.get_level()].get_value(current.get_row(), current.get_column() - 1) != 4
        && FullMap[current.get_level()].get_value(current.get_row(), current.get_column() - 1) != 3
        && FullMap[current.get_level()].get_value(current.get_row(), current.get_column() - 1) != 0){
            if(FullMap[current.get_level()].get_value(current.get_row(), current.get_column() - 1) == 1){
                discover = Coordinate<uint32_t>(current.get_level(), current.get_row(), current.get_column() - 1);
                coordinate_holder.push_back(discover);
                FullMap[current.get_level()].MapChange(current.get_row(), current.get_column() - 1, 3);
            }
            if(FullMap[current.get_level()].get_value(current.get_row(), current.get_column() - 1) == 2){
                discover = Coordinate<uint32_t>(current.get_level(), current.get_row(), current.get_column() + 1);
                coordinate_holder.push_back(discover);
                FullMap[current.get_level()].MapChange(current.get_row(), current.get_column() - 1, 4);
            }
            if(FullMap[current.get_level()].get_value(current.get_row(), current.get_column() - 1) == 2){
                hangar_found = true; 

            }
            number = number - 1;
            path[number] = 'w';
            if(hangar_found){
                 number = number + 1;
            }
           
            
        } // west, not elevator 
        if(current.get_level() > 0 && FullMap[current.get_level()].get_value(current.get_row(), current.get_column()) == 4
         && FullMap[current.get_level() - 1].get_value(current.get_row(), current.get_column()) != 5
         && FullMap[current.get_level() - 1].get_value(current.get_row(), current.get_column()) != 3
         && FullMap[current.get_level() - 1].get_value(current.get_row(), current.get_column()) != 4
         && FullMap[current.get_level() - 1].get_value(current.get_row(), current.get_column()) != 0){
            if(FullMap[current.get_level() - 1].get_value(current.get_row(), current.get_column()) == 2){
                discover = Coordinate<uint32_t>(current.get_level() - 1, current.get_row(), current.get_column());
                coordinate_holder.push_back(discover);
                FullMap[current.get_level() - 1].MapChange(current.get_row(), current.get_column(), 3);
            }
            if(FullMap[current.get_level() - 1].get_value(current.get_row(), current.get_column()) == 6){
                hangar_found = true; 
            }
            number = number + full;
            path[number] = 'g';
            if(!hangar_found){
                number = number - full;
            }
        

        } 
        // north elevator - check the same row, column but w diff level 

        if(current.get_level() < FullMap.size() && FullMap[current.get_level()].get_value(current.get_row(), current.get_column()) == 4
        && FullMap[current.get_level() + 1].get_value(current.get_row(), current.get_column()) != 5
        && FullMap[current.get_level() + 1].get_value(current.get_row(), current.get_column()) != 4
        && FullMap[current.get_level() + 1].get_value(current.get_row(), current.get_column()) != 3
        && FullMap[current.get_level() + 1].get_value(current.get_row(), current.get_column()) != 0){
            if(FullMap[current.get_level() + 1].get_value(current.get_row(), current.get_column()) == 2){
                discover = Coordinate<uint32_t>(current.get_level() + 1, current.get_row(), current.get_column());
                coordinate_holder.push_back(discover);
                FullMap[current.get_level() + 1].MapChange(current.get_row(), current.get_column(), 3);
            }
            if(FullMap[current.get_level() + 1].get_value(current.get_row(), current.get_column()) == 6){
                hangar_found = true; 
            }
            number = number - full;
            path[number] = 'h';
            if(!hangar_found){
                number = number + full;
            }
            
        } 
        // south elevator check w same but w diff level 
        if(!hangar_found){
            execute();
        }
        
    }
    void convert_index_to_coordinates(int number2, int size2, int& level, int& row, int& col) {
    level = number2 / (size2 * size2);
    row = (number2 % (size2 * size2)) / size2;
    col = (number2 % (size2 * size2)) % size2;
    }   

    void backtracking(){
    while(number != starting_number){
        if(path[number] == 'n'){
            number = number + size; 
            uint32_t level = number/full;
            uint32_t row = (number % (size * size)) / size;
            uint32_t col = (number % (size * size)) % size;
            FullMap[level].MapChange(row, col, 11);
            
        }
        if(path[number] == 'e'){
            number = number + 1;
            uint32_t level = number/full;
            uint32_t row = (number % (size * size)) / size;
            uint32_t col = (number % (size * size)) % size;
            FullMap[level].MapChange(row, col, 12);
        }
        if(path[number] == 's'){
            number = number - size;
            uint32_t level = number/full;
            uint32_t row = (number % (size * size)) / size;
            uint32_t col = (number % (size * size)) % size;
            FullMap[level].MapChange(row, col, 13);
            
        }
        if(path[number] == 'w'){
            number = number - 1;
            uint32_t level = number/full;
            uint32_t row = (number % (size * size)) / size;
            uint32_t col = (number % (size * size)) % size;
            FullMap[level].MapChange(row, col, 14);
        } 

        if(path[number] == 'g'){
            number = number - full;
            uint32_t level = number/full;
            uint32_t row = (number % (size * size)) / size;
            uint32_t col = (number % (size * size)) % size;
            FullMap[level].MapChange(row, col, level - 80);
            
        }

        if(path[number] == 'h'){
            number = number + full; 
            uint32_t level = number/full;
            uint32_t row = (number % (size * size)) / size;
            uint32_t col = (number % (size * size)) % size;
            FullMap[level].MapChange(row, col, level + 80);
            
        }


    }
    }

    void output_writing(){
        size_t level = FullMap.size();
        uint32_t rows = size;
        uint32_t cols = size; 
        for(uint32_t i = 0; i < level; i++){
            cout << "// level " << i;
            for(uint32_t j = 0; j < rows; j++){
                cout << "/n";
                for(uint32_t k = 0; k < cols; k++){
                    if(FullMap[i].get_value(j, k) == 1 || FullMap[level].get_value(j, k) == 3){
                        cout << ".";
                    }
                    if(FullMap[i].get_value(j, k) == 2 || FullMap[level].get_value(j, k) == 4){
                        cout << "E";
                    }
                    if(FullMap[i].get_value(j, k) == 0){
                        cout << "S ";
                    }
                    if(FullMap[i].get_value(j, k) == 5){
                        cout << "# ";
                    }
                    if(FullMap[i].get_value(j, k) == 6){
                        cout << "H ";
                    }
                    if(FullMap[i].get_value(j, k) == 11){
                        cout << "n ";
                    }
                    if(FullMap[i].get_value(j, k) == 12){
                        cout << "e ";
                    }
                    if(FullMap[i].get_value(j, k) == 13){
                        cout << "s ";
                    }
                    if(FullMap[i].get_value(j, k) == 14){
                        cout << "w ";
                    }
                    if(FullMap[i].get_value(j, k) >= 80){
                        cout << to_string(i - 80) << " ";
                    }  
                    if(static_cast<int>(FullMap[i].get_value(j, k)) <= -80){
                        cout << to_string(i + 80) << " ";
                    }          
                }
            }
        }
    }

    void output_writhing(){
        for(uint32_t i = 0; i < FullMap.size(); i++){
            for(uint32_t j = 0; j < size; j++){
                for(uint32_t k = 0; k < size; k++){
                    if(FullMap[i].get_value(j, k) == 11){
                        cout << "(" << i << ", " << j << ", " << k << ", n)" << "/n";
                    }
                    if(FullMap[i].get_value(j, k) == 12){
                        cout << "(" << i << ", " << j << ", " << k << ", e)" << "/n";
                    }
                    if(FullMap[i].get_value(j, k) == 13){
                        cout << "(" << i << ", " << j << ", " << k << ", s)" << "/n";
                    }
                    if(FullMap[i].get_value(j, k) == 14){
                        cout << "(" << i << ", " << j << ", " << k << ", w)" << "/n";
                    }
                    if(FullMap[i].get_value(j, k) >= 80){
                        cout << "(" << i << ", " << j << ", " << k << ", " << to_string(i - 80) << ")" << "/n";
                    }
                    if(FullMap[i].get_value(j, k) < 80){
                        cout << "(" << i << ", " << j << ", " << k << ", " << to_string(i + 80) << ")" << "/n";
                    }
                }
            }
        }
    }
};

void print_help() {
    cout << "Usage: ./ship [--stack | --queue] [--output M|L] < infile > outfile\n";
    cout << "--stack, -s    Use stack for DFS\n";
    cout << "--queue, -q    Use queue for BFS\n";
    cout << "--output M|L, -o M|L   Output mode (M = map, L = list)\n";
    cout << "--help, -h    Show this message\n";
}

int main(int argc, char* argv[]) {
    bool use_stack = false, use_queue = false;
    char output_mode = 'M'; // Default to map format
    int option_index = 0;
    struct option long_options[] = {
        {"stack", no_argument, 0, 's'},
        {"queue", no_argument, 0, 'q'},
        {"output", required_argument, 0, 'o'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "sqo:h", long_options, &option_index)) != -1) {
        switch (opt) {
            case 's':
                if (use_queue) {
                    cerr << "Error: Cannot specify both stack and queue.\n";
                    return 1;
                }
                use_stack = true;
                break;
            case 'q':
                if (use_stack) {
                    cerr << "Error: Cannot specify both stack and queue.\n";
                    return 1;
                }
                use_queue = true;
                break;
            case 'o':
                if (optarg[0] == 'M' || optarg[0] == 'L') {
                    output_mode = optarg[0];
                } else {
                    cerr << "Error: Invalid output mode. Use 'M' or 'L'.\n";
                    return 1;
                }
                break;
            case 'h':
                print_help();
                return 0;
            default:
                cerr << "Error: Invalid arguments.\n";
                return 1;
        }
    }

    if (!use_stack && !use_queue) {
        cerr << "Error: You must specify either stack or queue.\n";
        return 1;
    }


    
    // Reading input from stdin (e.g., redirected file)
    char morq;
    cin >> morq;

    bool mol = false;
    if(morq == 'M' && output_mode == 'M'){
        mol = true; 
    }
    uint32_t levels, total;
    cin >> levels;
    cin >> total;
    uint32_t rows = total;
    uint32_t cols = total;

    string comment; 
    char floors;

    vector<Array<uint32_t>> array_searcher;
    Coordinate<uint32_t> starterco; 
    array_searcher.resize(levels, Array<uint32_t>(rows));

    if(mol == true){
    for (uint32_t l = 0; l < levels; ++l) {
        getline(cin, comment); //getline 
        for (uint32_t r = 0; r < rows; ++r) {
            for(uint32_t c = 0; c < cols; c++){
                cin >> floors; 
                if(floors == '.'){
                    array_searcher[l].MapChange(r, c, 1);
                }
                if(floors == '#'){
                    array_searcher[l].MapChange(r, c, 5);
                }
                if(floors == 'E'){
                    array_searcher[l].MapChange(r, c, 2);
                }
                if(floors == 'S'){
                    array_searcher[l].MapChange(r, c, 0);
                    starterco.changer(l, r, c);
                }
            }
        }
    }
    }
    if(mol == false){
    for (uint32_t l = 0; l < levels; ++l) {
        for (uint32_t r = 0; r < rows; ++r) {
            char paren; 
            char comma;
            uint32_t level0;
            uint32_t row0;
            uint32_t col0;
            char there;
            cin >> paren;
            cin >> level0;
            cin >> comma;
            cin >> row0;
            cin >> comma;
            cin >> col0;
            cin >> comma;
            cin >> there; 
            uint32_t substitute; 
                if(there == '.'){
                    substitute = 1;
                }
                if(there == '#'){
                   substitute = 5; 
                }
                if(there == 'E'){
                    substitute = 2;
                }
                if(there == 'S'){
                    substitute = 0; 
                    starterco.changer(level0, row0, col0);
                }
            array_searcher[level0].MapChange(row0, col0, substitute);    
        }
    }
    }


// router bools: sorq, array of vectors, starting coordinate 
    Router routesearcher(use_stack, array_searcher, starterco); //check 
    while(!routesearcher.is_hangar_found()){
        routesearcher.routing_process();
    }
    routesearcher.backtracking();
    if(mol){
    routesearcher.output_writing();
    }
    if(mol){
    routesearcher.output_writhing();
    }

    return 0;
}

