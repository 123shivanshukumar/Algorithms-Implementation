#include<iostream>
#include<unordered_map>
#include<queue>
#include<string>
#include<fstream>

#include<vector>
class Student{
    int id; // unique 
    std::string name;
    public:
        Student(){} // can initalise string with char* 
        void get_name(){std::cout<<name;}
        int get_id(){return id;}
        friend std::istream& operator>>(std::istream&,Student&);
};
std::istream& operator>>(std::istream& stream,Student& stud){
    int s_id;std::string s;
    stream>>s_id>>s;
    stud.id = s_id;
    stud.name = s;
    return stream;
}
class Course{
    int id;
    std::string name;
    public:
        Course(){}
        int get_id(){return id;}
        void get_name(){std::cout<<name;}
        friend std::istream& operator>>(std::istream&,Course&);
};
std::istream& operator>>(std::istream& stream,Course& course){
    int s_id;std::string s;
    stream>>s_id>>s;
    course.id = s_id;
    course.name = s;
    return stream;
}
class System{
    //generate test cases by yukash
    // std::unordered_map<int,Student>student_list;
    // std::unordered_map<int,Course>course_list;

    //std::unordered_map<int,int>course_indices; //  given the course id what is the index in the matching vector
    int n;
    std::unordered_map<int,int>matching;
    std::unordered_map<int,std::vector<int>>stud_preference;
    std::unordered_map<int,std::unordered_map<int,int>>course_preference;
    public:
        System(){}
        friend std::istream& operator>>(std::istream&, System&);
        void print();//
        friend std::ostream& operator<<(std::ostream&, System&);
        void gale_shapley();

};
std::ostream& operator<<(std::ostream& stream, System& sys){
    for(auto it: sys.matching){
        // course_list[it.first].get_name();
        // std::cout<<" is given to ";
        // student_list[it.second].get_name(); // tied together
        // std::cout<<std::endl;
        stream<<"course "<<it.first<<" is matched to "<<"student "<<it.second<<std::endl;
    }
    return stream;
}
void System::gale_shapley(){
    std::queue<int>unmatched_students;
    std::unordered_map<int,int>stud_last_applied;
    for(int j = 0; j < n; j++ ){
        unmatched_students.push(j+1); // push the id of the student 
        stud_last_applied[j+1] = 0; // set last applied index of all students to 0
    }
    int course_id,stud_id,matched_student,course_index;
    while(!unmatched_students.empty()){
        stud_id  = unmatched_students.front(); // get the first unmatched student
        course_index = stud_last_applied[stud_id]; // get the index of last applied 
        course_id = stud_preference[stud_id][course_index]; // fetch from the vector
        if(matching.find(course_id) == matching.end()){
            matching[course_id] = stud_id;
            unmatched_students.pop();
        }
        else{
            matched_student = matching[course_id];
            if(course_preference[course_id][matched_student] > course_preference[course_id][stud_id]){
                stud_last_applied[matched_student]++; // increase its index
                matching[course_id] = stud_id; // change the mapping
                unmatched_students.pop();
                unmatched_students.push(matched_student);
            }
            else{
                stud_last_applied[stud_id]++; // dont pop!
            }
        }
    }
}
std::istream& operator>>(std::istream& stream, System& sys){
    int size;
    stream>>size;    
    sys.n = size;
    // Student stud;
    // Course course;
    // int stud_id, course_id;
    // for(int j = 0; j < sys.n; j++){
    //     std::cin>>stud>>course;
    //     stud_id = stud.get_id();
    //     course_id = course.get_id();
    //     sys.course_list[course_id] = course;
    //     sys.student_list[stud_id] = stud;
    // }
    // std::vector<int>row(size);
    //input the course preferecne 
    int course_id,stud_id;
    for(int j = 0; j < size ; j++){
        for(int i = 0; i < size; i++){ //input is the id of student 
            stream>>stud_id;
            sys.course_preference[j+1][stud_id] = i; // will create j when called for the first time 
        }
    }
    // input the course preference 
    std::vector<int>temp;
    for(int j = 0; j < size ; j++){
        sys.stud_preference[j+1] = temp;
        sys.stud_preference[j+1].resize(size);
        for(int i = 0; i < size; i++){
            stream>>course_id;
            sys.stud_preference[j+1][i] = course_id;
        }
    }
    return stream;
}
void System::print(){//std::ofstream& file_out
    
}
int main(){
    std::string input = "input00.txt"; // filename[6]
    std::string output = "output00.txt";
    for(int j = 0 ; j < 10; j++)
    {   
        System sys;
        input[6] = '0'+j;
        output[7] = '0'+j;
        std::ifstream file_in(input);
        file_in>>sys;
        std::ofstream file_out(output);
        sys.gale_shapley();
        file_out<<sys;// yyaay
    }
}

