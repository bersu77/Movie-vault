#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Movie {
    string movie_name;
    int released_year;
    double rating;
    string genre;
    string where_to_watch;
    string country;
    string language;
};

void work();
void comments();
void accept(std::vector<Movie>& movies);
void write_to_csv(const std::vector<Movie>& movies,string file_exist_before);
void read_from_csv(const std::string& name);
void upgrade();
string read_password();

int main() {
   work();
    return 0;
}

void work(){
    vector<Movie> movies;
    int count=0;
    string identity,password,name;
    cout<<"are you an admin or searcher :";
    cin>>identity;
    while(identity!="admin" && identity!="searcher"){
        cout<<"please,enter the correct identity of yours :";
        cin>>identity;
    } 
    cin.ignore(); 
    system("cls");
    if (identity=="admin"){
        while (count<3){
            cout<<"enter the password :";
            getline(cin,password);
            system("cls");
            if (password==read_password()){
                break;
            }
            else{
                cout<<"you have entered the wrong password "<<endl;
                count++;
            }
        }
        while(true){
            if (password==read_password()){
                string choice;
                system("cls");
                cout<<"what do you want add new film or edit an exiting file or exit(add/edit/exit):";
                cin>>choice;
                if (choice=="add"){
                    string file_exist_before;
                    cout<<"is there a previous file created (yes or no) :";
                    cin>>file_exist_before;
                    cin.ignore();
                    accept(movies);
                    write_to_csv(movies,file_exist_before);
                }
                else if(choice =="edit"){
                    cin.ignore();
                    upgrade();
                }
                else if(choice=="exit"){
                    cout<<"you exit";
                    break;
                }
                    
            }
        }
            
        
    
    }
    else if(identity=="searcher"){
        while(true){
            system("cls");
            cout<<"enter the movie name";
            getline(cin,name);
            read_from_csv(name);
            string error;
            cout<<"is there an error in the file or do you want to write your comment('yes or no') :";
            cin>>error;
            if (error=="yes"){
                comments();
            }
            string again;
            cout<<"do you want to search again('yes or no') :";
            cin>>again;
            if (again=="no"){
                break;
            }
        }
        cout<<"we hope you get useful information";
    }
    
}

void accept(vector<Movie>& movies) {
    string is_there_another;
    while (is_there_another!="no") {
        Movie movie;
        system("cls");
        cout<<"cout enter the movie name :";
        getline(cin,movie.movie_name);
        system("cls");
        cout << "Enter the released year: ";
        cin >> movie.released_year;
        system("cls");
        cout << "Enter the rating: ";
        cin >> movie.rating;
        cin.ignore();
        system("cls");
        cout<<"Enter the movie genre :";
        getline(cin,movie.genre);
        system("cls");
        cout<<"where the film made :";
        cin>>movie.country;
        system("cls");
        cout<<"the original language that the movie released :";
        cin>>movie.language;
        system("cls");
        cin.ignore();
        cout<<"enter where to watch the movie ";
        getline(cin,movie.where_to_watch);
        system("cls");
        movies.push_back(movie);
        cout << "Is there another movie('yes' or 'no') :";
        cin >> is_there_another;
        cin.ignore();
    }
}

void write_to_csv(const vector<Movie>& movies,string file_exist_before) {
    ofstream file("movies.csv",ios::app);
    if (file.is_open()) {
        if (file_exist_before=="no"){
        file << "film_name,Released Year,Rating,Genre,Country,Language,Where to watch\n";
        }
        for (const Movie& movie : movies) {
            file <<movie.movie_name<<","<< movie.released_year << "," << movie.rating << "," << movie.genre<<"," <<movie.country<<","<<movie.language<<","<<movie.where_to_watch<< "\n";
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }
}

void read_from_csv(const string &name){
    ifstream file("movies.csv");
    string array[7]={"film_name","Released Year","Rating","Genre","Country","Language","Where to watch"};
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream ss(line);
            string cell;
            getline(ss, cell, ',');
            if (cell == name) {
                cout << left << setfill('_') << setw(20) <<array[0]<<cell<<endl;
                int i=1;
                while(getline(ss,cell,','))
                {   if (i<=6){}
                    cout << left << setfill('_') << setw(20) <<array[i]<<cell<<endl;
                    i++;
                }
            }
        }
        while (getline(file, line)) {
            istringstream ss(line);
            string cell;
            getline(ss, cell, ',');
            if (cell != name){
                cout<<"the movie you are searching for doesnot exit in the server"<<endl;
            }
        }
    }
         else {
        std::cout << "Unable to open file";
    }
    
}

string read_password() {
    string password;
    ifstream file("password.txt");
    if (file.is_open()) {
        getline(file, password);
        file.close();
    } else {
        cout << "Unable to open file";
    }
    return password;
}
void comments(){
    string note;
    ofstream comment("comment.txt",ios::app);
    if(comment.is_open()){
        cout<<"write the error you got and the comment :";
        cin.ignore();
        getline(cin,note);
        comment<<note;
        comment.close();
    }
    else{
        cout<<"unable to open the file";
    }
}

void upgrade(){
    string old_movie_name, new_movie_name;
    string arr[7]={"film_name","Released Year","Rating","Genre","Country","Language","Where to watch"};
    string again;
    while(again!="no"){
        cout<<"Enter the movie name you want to edit: ";
        cin>>old_movie_name;
        cin.ignore();
        system("cls");
        cout<<"Enter the new movie name: ";
        cin>>new_movie_name;
        cin.ignore();  
        system("cls");
        ifstream file("movies.csv");
        if(file.is_open()){
            vector<string>rows;
            string line;
            while(getline(file,line)){
                rows.push_back(line);
            }
            file.close();
            for(size_t i=0;i<rows.size();i++){
                istringstream ss(rows[i]);
                string cell;
                getline(ss,cell,',');
                if(cell==old_movie_name){
                    rows[i].clear();
                    ostringstream oss;
                    oss<<new_movie_name;
                    for(int j=1;j<7;j++){
                        string corrected_info;
                        cout<<arr[j]<<" :";
                        getline(cin,corrected_info);
                        system("cls");
                        oss<<","<<corrected_info;
                    }
                    rows[i]=oss.str();
                }
            }
            ofstream new_file("movies.csv");
            if(new_file.is_open()){
                for(size_t i=0;i<rows.size();i++){
                    new_file<<rows[i]<<"\n";
                }
            }
        }
        cout<<"Is there another movie you want to edit? ";
        cin>>again;
        cin.ignore();  // Add this line
    }        
}
