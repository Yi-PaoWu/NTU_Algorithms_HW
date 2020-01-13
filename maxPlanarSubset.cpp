#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
using namespace std;

void output_chord(int ,int ,int** ,int** ,vector<int>&);

int main(int argc, char* argv[]){


	// ===== READ FILE ======= //
	ifstream file;
	file.open(argv[1],ios::in);
	vector<int> data;
	int num;
	if (file.is_open()){
		while(file >> num) data.push_back(num);
	}
	file.close();
	for (int i=0;i<data.size();i++){
		//cout << data[i] << '\n';
	}

	// ====== MPS ====== //
	
	int vetrices = data[0];
	cout<<"vetrices = "<<vetrices<<endl;
	int** MIS = new int*[vetrices-1];
	int** chords_ans_x = new int*[vetrices-1];
	int** chords_ans_y = new int*[vetrices-1];
	for(int i=0;i<vetrices-1;i++){
		MIS[i] = new int[vetrices-1];
		chords_ans_x[i] = new int[vetrices-1];
		chords_ans_y[i] = new int[vetrices-1];
		MIS[i][i] = 0;
	}

	int** chord =  new int*[vetrices/2];
	for(int i=0;i<=vetrices/2;i++){
		chord[i] = new int[2];
	}

	for(int j=0;j<vetrices/2;j++){
		chord[j+1][0] = data[2*j+1];
		chord[j+1][1] = data[2*j+2];  
		//cout<<"chord["<<j+1<<"][0] = "<< data[2*j+1]<<endl;
		//cout<<"chord["<<j+1<<"][1] = "<< data[2*j+2]<<endl;
	}

	int** chords =  new int*[vetrices];
	for(int i=0;i<=vetrices;i++){
		chords[i] = new int[2];
	}

	for(int h=0;h<vetrices;h++){
		for(int k=1;k<=vetrices/2;k++){
			if(chord[k][0] == h){
				chords[h][0] = h;
				chords[h][1] = chord[k][1];
				//cout<<"chords["<<h<<"][0] = "<<h<<", chords["<<h<<"] = "<<chords[h][1]<<endl;
				break;
			}
			else if(chord[k][1] == h){
				chords[h][0] = h;
				chords[h][1] = chord[k][0];
				//cout<<"chords["<<h<<"][0] = "<<h<<", chords["<<h<<"] = "<<chords[h][1]<<endl;
				break;
			}
		}
	}

	for(int l=1;l<=vetrices-1;l++){
		//cout<<"------- l = "<<l<<" --------"<<endl;
		for(int i=0;(i+l)<vetrices;i++){ // l : between i and j

			if( chords[i+l][1] >i && chords[i+l][1] <(i+l) )  { // case 2
				if( (MIS[i][chords[i+l][1]-1]+MIS[chords[i+l][1]+1][i+l-1]+1) > MIS[i][i+l-1] ){
					MIS[i][i+l] = MIS[i][chords[i+l][1]-1]+MIS[chords[i+l][1]+1][i+l-1]+1;
					chords_ans_x[i][i+l] = chords[i+l][1];
					chords_ans_y[i][i+l] = chords[i+l][0];
				}
				else{
					MIS[i][i+l] = MIS[i][i+l-1];
				}
				//cout<<"case2 :MIS["<<i<<"]["<<i+l<<"] = "<<MIS[i][i+l]<<endl;
			}
			else if( chords[i+l][1] == i){ // case 3
				MIS[i][i+l] = MIS[i+1][i+l-1]+1;
				chords_ans_x[i][i+l] = chords[i+l][1];
				chords_ans_y[i][i+l] = chords[i+l][0];
				//cout<<"case3 :MIS["<<i<<"]["<<i+l<<"] = "<<MIS[i][i+l]<<endl;
			}
			else { //case 1
				MIS[i][i+l] = MIS[i][i+l-1];
				chords_ans_x[i][i+l] = 0;
				chords_ans_y[i][i+l] = 0;
				//cout<<"case1 :MIS["<<i<<"]["<<i+l<<"] = "<<MIS[i][i+l]<<endl;
			}
			
		}
	}


	cout<<"MIS[0][2n-1] = "<<MIS[0][vetrices-1]<<endl;
	//cout<<chords_ans_x[0][4]<<" "<<chords_ans_y[0][4]<<endl;
	vector<int> ans;

	output_chord(0,vetrices-1,chords_ans_x,chords_ans_y,ans);
	
	// ====== insertion sort ===== //

    int temp = 0;
	int temp_2 =0;
	
	cout<<"ans.size() = "<<ans.size()<<endl;
    for(int i = 0 ; i < (ans.size()) ; i += 2){
		temp = ans[i];
		temp_2 = ans[i+1];
		int j = i;
	    while ((ans[j-2] > temp)&&(j>0)){
			ans[j] = ans[j-2];
			ans[j+1] = ans[j-1];
			j-= 2;
		}	
		ans[j] = temp;
		ans[j+1] = temp_2;
		
	}


	// ====== WRITE FILE ======= //

	ofstream file2;
	file2.open(argv[2],ios::out);
	file2<<vetrices<<endl;
	if (file2.is_open()){
		for (int i=0;i<ans.size();i+=2){
			file2<<ans[i]<<" "<<ans[i+1]<<'\n';
			cout<<ans[i]<<" "<<ans[i+1]<<endl;
		}
	}
	file2.close();
	delete [] chords_ans_x;
	delete [] chords_ans_y;
	delete [] chords;
	delete [] chords;
	delete [] MIS;
    
	return 0 ;
}

void output_chord(int x,int y,int** chords_ans_x,int** chords_ans_y,vector<int>& ans){
	int chord_x = 0;
	int chord_y = 0;
	//cout<<"(x,y) = ("<<x<<","<<y<<")"<<endl;
	if( (chords_ans_x[x][y] != 0 || chords_ans_y[x][y] != 0) && (y>x) )  {
		//cout<<"ans_x["<<x<<"]["<<y<<"] : "<<chords_ans_x[x][y]<<" ans_["<<x<<"]["<<y<<"] : "<<chords_ans_y[x][y]<<endl;
		ans.push_back(chords_ans_x[x][y]);
		ans.push_back(chords_ans_y[x][y]); 
		chord_x = chords_ans_x[x][y];
		chord_y = chords_ans_y[x][y];
		if(x < chord_x) {
			//cout<<"--- (  "<<x<<" , "<<chord_x-1<<" ) ---"<<endl;
			output_chord(x,chord_x-1,chords_ans_x,chords_ans_y,ans);	
		}
		if(chord_x != chord_y){ 
			//cout<<"--- (  "<<chord_x+1<<" , "<<chord_y-1<<" ) ---"<<endl;
			output_chord(chord_x+1,chord_y-1,chords_ans_x,chords_ans_y,ans);	
		}
		//if(y > chord_y)output_chord(chord_x+1,y,chords_ans_x,chords_ans_y);	
	}
	else if(chords_ans_x[x][y] == 0 && chords_ans_y[x][y] == 0 && (y>x)){
		output_chord(x,y-1,chords_ans_x,chords_ans_y,ans);
	}
	
}
//13 ,177 wrong!!!!!!!!