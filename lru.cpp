#include <bits/stdc++.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;
int pidcounter=0;
int M = 0;
int V = 0;
int P = 0;
int freeM=0;
int freeV=0;
fstream out("ofile",ios::app);
vector<int>mainbool;
vector<int>swapbool;
vector<int>mainmem;
vector<int>swapmem;
list<pair<int,int>>lru;
map<int,pair<int,int>>mp;
class executable{
    public:
    string execfile;
    int pid;
    bool iskill;
    vector<bool>isinmain;
    map<int,int>pagetable;
   executable(){
    pid=-1;
   }
    void run(vector<executable>&arr){
      ifstream runfile(execfile);
      int address=isinmain.size()*P;
      string line;
      getline(runfile,line);
      while(getline(runfile,line)){
        stringstream i(line);
        string inst;
        i >> inst;
        if(inst=="add"){
          string x1;
          i >> x1;
          string x;
          for(int i=0;i<x1.size()-1;i++){
            x+=x1[i];
          }
          string y1;
          i >> y1;
          string y;
           for(int i=0;i<y1.size()-1;i++){
            y+=y1[i];
          }
          string z;
          i >> z;
          int xnum=stoi(x);
          int ynum=stoi(y);
          int znum=stoi(z);
          if((xnum>=address)||(ynum>=address)||(znum>=address)||(xnum<0)||(ynum<0)||(znum<0)){
            if((xnum>=address)||(xnum<0)){
            out<<" Invalid Memory Address "<<xnum<<" specified for process id "<<pid<<endl;
            } 
            else if((ynum>=address)||(ynum<0)){
            out<<" Invalid Memory Address "<<ynum<<" specified for process id "<<pid<<endl;
            }
            else if((znum>=address)||(znum<0)){
            out<<" Invalid Memory Address "<<znum<<" specified for process id "<<pid<<endl;
            }
          }
          else{
          int temp1=xnum/P;
          int add1,add2,result;
          if(isinmain[temp1]==0){
             swapinto(temp1,arr);
          }
          add1=mainmem[pagetable[temp1]*P+(xnum-temp1*P)];
           lru.remove({pagetable[temp1],pid});
          lru.push_front({pagetable[temp1],pid});
          int temp2=ynum/P;
          if(isinmain[temp2]==0){
             swapinto(temp2,arr);
          }
           add2=mainmem[pagetable[temp2]*P+(ynum-temp2*P)];
            lru.remove({pagetable[temp2],pid});
            lru.push_front({pagetable[temp2],pid});
          int temp3=znum/P;
           if(isinmain[temp3]==0){
             swapinto(temp3,arr);
          }
             result=add1+add2;
             mainmem[pagetable[temp3]*P+(znum-temp3*P)]=result;
              lru.remove({pagetable[temp3],pid});
               lru.push_front({pagetable[temp3],pid});
        out<<"Command: "<<inst<<" "<<x<<" "<<y<<" "<<z<<";"<<"Result:"<<" Value in addr "<<x<<"="<<add1<<","<<"addr "<<y<<"="<<add2<<","<<"addr "<<z<<"="<<result<<endl;
          }
        }
        else if(inst=="sub"){
          string x1;
          i >> x1;
          string x;
          for(int i=0;i<x1.size()-1;i++){
            x+=x1[i];
          }
          string y1;
          i >> y1;
          string y;
           for(int i=0;i<y1.size()-1;i++){
            y+=y1[i];
          }
          string z;
          i >> z;
          int xnum=stoi(x);
          int ynum=stoi(y);
          int znum=stoi(z);
          if((xnum>=address)||(ynum>=address)||(znum>=address)||(xnum<0)||(ynum<0)||(znum<0)){
            if((xnum>=address)||(xnum<0)){
            out<<" Invalid Memory Address "<<xnum<<" specified for process id "<<pid<<endl;
            } 
            else if((ynum>=address)||(ynum<0)){
            out<<" Invalid Memory Address "<<ynum<<" specified for process id "<<pid<<endl;
            }
            else if((znum>=address)||(znum<0)){
            out<<" Invalid Memory Address "<<znum<<" specified for process id "<<pid<<endl;
            }
          }
          else{
          int temp1=xnum/P;
          int sub1,sub2,result;
          if(isinmain[temp1]==0){
             swapinto(temp1,arr);
          }
           sub1=mainmem[pagetable[temp1]*P+(xnum-temp1*P)];
            lru.remove({pagetable[temp1],pid});
            lru.push_front({pagetable[temp1],pid});
          int temp2=ynum/P;
          if(isinmain[temp2]==0){
             swapinto(temp2,arr);
          }
           sub2=mainmem[pagetable[temp2]*P+(ynum-temp2*P)];
            lru.remove({pagetable[temp2],pid});
           lru.push_front({pagetable[temp2],pid});
          int temp3=znum/P;
           if(isinmain[temp3]==0){
             swapinto(temp3,arr);
          }
            result=sub1-sub2;
             mainmem[pagetable[temp3]*P+(znum-temp3*P)]=result;
              lru.remove({pagetable[temp3],pid});
              lru.push_front({pagetable[temp3],pid});
       out<<"Command: "<<inst<<" "<<x<<" "<<y<<" "<<z<<";"<<"Result:"<<" Value in addr "<<x<<"="<<sub1<<","<<"addr "<<y<<"="<<sub2<<","<<"addr "<<z<<"="<<result<<endl;
          }
        }
        else if(inst=="print"){
          string x;
          i >> x;
          int xnum=stoi(x);
          if((xnum>=address)||(xnum<0)){
             out<<" Invalid Memory Address "<<xnum<<" specified for process id "<<pid<<endl;
          }
          else{
          int temp1=xnum/P;
          if(isinmain[temp1]==0){
            swapinto(temp1,arr);
           }
           lru.remove({pagetable[temp1],pid});
           lru.push_front({pagetable[temp1],pid});
          out<<"Command: "<<inst<<" "<<x<<";"<<"Result:"<<" Value in addr "<<x<<"="<<mainmem[pagetable[temp1]*P+(xnum-temp1*P)]<<endl;
          }
        }
        else if(inst=="load"){
          string x1;
          i >> x1;
           string x;
           for(int i=0;i<x1.size()-1;i++){
            x+=x1[i];
          }
          string y;
          i >> y;
          int xnum=stoi(x);
          int ynum=stoi(y);
          if((ynum>=address)||(ynum<0)){
             out<<" Invalid Memory Address "<<ynum<<" specified for process id "<<pid<<endl;
          }
          else{
          int temp1=ynum/P;
          if(isinmain[temp1]==0){
            swapinto(temp1,arr);
          }
           lru.remove({pagetable[temp1],pid});
           lru.push_front({pagetable[temp1],pid});
        out<<"Command: "<<inst<<" "<<x<<","<<y<<";"<<"Result:"<<" Value of "<<x<<" is now stored in addr "<<y<<endl;
           mainmem[pagetable[temp1]*P+(ynum-temp1*P)]=xnum;
          }
        }
      }
    }
 void swapinto(int temp,vector<executable>& arr){
  int f=0;
  for(int i=0;i<mainbool.size();i++){
    if(mainbool[i]==0){
      int j=pagetable[temp]*P;
      for(int k=i*P;k<(i+1)*P;k++){
        mainmem[k]=swapmem[j];
        j++;
      }
      swapbool[pagetable[temp]]=0;
      pagetable[temp]=i;
      mp[i]={temp,pid};
      isinmain[temp]=1;
      mainbool[i]=1;
      freeM--;
      freeV++;
      f=1;
      lru.push_front({i,pid});
      break;
    }  
  }
  if(f==0){
     pair<int,int> x=lru.back();
     lru.pop_back();
     int fut=pagetable[temp];
     pagetable[temp]=x.first;
    for(auto it=arr[x.second].pagetable.begin();it!=arr[x.second].pagetable.end();it++){
      if((it->second==x.first)&&(arr[x.second].isinmain[it->first]==1)){
         arr[x.second].isinmain[it->first]=0;
         arr[x.second].pagetable[it->first]=fut;
         int j=fut*P;
         for(int i=x.first*P;i<=(x.first+1)*P;i++){
            int now=swapmem[j];
          swapmem[j]=mainmem[i];
          mainmem[i]=now;
          j++;
         }
        break;
      }
    }
      mp[x.first]={temp,pid};
     lru.push_front({x.first,pid});
     isinmain[temp]=1;
  }
}
};

 vector<executable>a(10000);
void allocatepages(int noofpages,map<int,int>&pt,int f,int pid1,vector<bool>&ismain){
    int j=0;
    for(int i=0;i<mainbool.size()&&j<noofpages;i++){
        if(mainbool[i]==0){
          pt[j]=i;
          mp[i]={j,pid1};
          lru.push_front({i,pid1});
          ismain[j]=1;
          j++;
          mainbool[i]=1;
        }
    }
    if(j<=noofpages){
    for(int i=0;i<swapbool.size()&&j<noofpages;i++){
        if(swapbool[i]==0){
          pt[j]=i;
          ismain[j]=0;
          j++;
          swapbool[i]=1;
        }
    }  
    }   
}
int main(int argc, char *argv[]){
    string infile;
    string outfile;
    int opt;
    while ((opt = getopt(argc, argv, "M:V:P:i:o:")) != -1) {
        switch (opt) {
            case 'M': M =atoi(optarg); break;
            case 'V': V =atoi(optarg); break;
            case 'P': P =atoi(optarg); break;
            case 'i': infile = optarg; break;
            case 'o':outfile = optarg; break;
            default:
                cerr << "Usage: " << argv[0] << " -M <size> -V <size> -P <size> -i <inputfile> -o <outputfile>" << std::endl;
                return EXIT_FAILURE;
        }
    }
    freeM=M*1024/P;
    mainbool.resize(M*1024/P);
    swapbool.resize(V*1024/P);
    mainmem.resize(M*1024);
    swapmem.resize(V*1024);
    freeV=V*1024/P;
    ifstream inputfile(infile);
    string line;
    while(getline(inputfile,line)){
        stringstream i(line);
        string command;
        string somefile;
        i >> command;
      if(command=="load"){
        vector<string>files;
      while(i >> somefile){
        files.push_back(somefile);
      }
      for(int j=0;j<files.size();j++){
        ifstream thisfile(files[j]);
        if(!thisfile){
            out<<files[j]<<" could not be loaded - file does not exist"<<endl;
        }
        else{
            string t;
            getline(thisfile,t);
            int filesize=stoi(t);
            int noofpages=1024*filesize/P;
            if(noofpages<=(freeM)){
                executable req;
                pidcounter++;
                req.pid=pidcounter;
                req.isinmain.resize(noofpages);
                req.iskill=0;
                req.execfile=files[j];
                map<int,int>pt;
                allocatepages(noofpages,pt,1,req.pid,req.isinmain);
                req.pagetable=pt;
                a[req.pid]=req;   
                freeM-=noofpages;
                out<<files[j]<<"  is loaded and is assigned process id "<<req.pid<<endl;             
            }
            else if(noofpages<=(freeV+freeM)){
                 executable req;
                pidcounter++;
                req.pid=pidcounter;
                req.isinmain.resize(noofpages);
                req.iskill=0;
                req.execfile=files[j];
                map<int,int>pt;
                allocatepages(noofpages,pt,0,req.pid,req.isinmain);
                req.pagetable=pt;
                a[req.pid]=req;  
                freeV-=(noofpages-freeM);
                freeM=0;
                out<<files[j]<<"  is loaded and is assigned process id "<<req.pid<<endl;
            }
            else{
                out<<files[j]<<" could not be loaded - memory is full"<<endl;
            }     
        }
    }
      }
      else if(command=="run"){
        string pid1;
        i>>pid1;
        int runpid=stoi(pid1);
        if((runpid<=0)||(runpid>pidcounter)||(a[runpid].iskill==1)){
          out<<"Invalid PID "<<runpid<<endl;
        }
        else{
          a[runpid].run(a);
        } 
      }
      else if(command=="kill"){
        string pid1;
        i >> pid1;
        int killpid=stoi(pid1);
        if((killpid<=0)||(killpid>pidcounter)){
          out<<"Invalid PID "<<killpid<<endl;
        }
        else{
          a[killpid].iskill=1;
          for(auto it=a[killpid].pagetable.begin();it!=a[killpid].pagetable.end();it++){
            if(a[killpid].isinmain[it->first]==1){
            mainbool[it->second]=0;
            freeM++;
            }
            else{
                swapbool[it->second]=0;
                freeV++;
            }
          }
          a[killpid].pagetable.clear();
          for(auto it=lru.begin();it!=lru.end();it++){
            if(it->second==killpid){
              lru.remove({it->first,it->second});
            }
          }
          out<<"killed"<<" "<<killpid<<endl;
        }

      }
      else if(command=="listpr"){
        vector<int>listofall;
        for(int ii=0;ii<a.size();ii++){
            if((a[ii].pid!=-1)&&(a[ii].iskill==0)){
              listofall.push_back(a[ii].pid);
            }
        }
       sort(listofall.begin(),listofall.end());
       for(int ii=0;ii<listofall.size();ii++){
        out<<listofall[ii]<<" ";
       }
       out<<endl;

      }
      else if(command=="pte"){
        string pid1;
        i >> pid1;
        int ptepid=stoi(pid1);
        string fileforpte;
        i >> fileforpte;
        if((ptepid<=0)||(ptepid>pidcounter)){
           out<<"Invalid PID "<<ptepid<<endl; 
        }
        else{
          fstream outpte(fileforpte+".txt",ios::app);
          auto now = chrono::system_clock::now();
          time_t currentTime = chrono::system_clock::to_time_t(now);
          tm localTime = *localtime(&currentTime);
          outpte << put_time(&localTime, "%a %b %d %I:%M:%S %p IST %Y") << endl;
           for(auto it=a[ptepid].pagetable.begin();it!=a[ptepid].pagetable.end();it++){
           outpte<<it->first<<" "<<it->second<<" "<<a[ptepid].isinmain[it->first]<<endl;
           }
        }
      }
      else if(command=="pteall"){
        string fileforpte;
        i >> fileforpte;
          fstream outpte(fileforpte+".txt",ios::app);
          auto now = chrono::system_clock::now();
          time_t currentTime = chrono::system_clock::to_time_t(now);
          tm localTime = *localtime(&currentTime);
          outpte << put_time(&localTime, "%a %b %d %I:%M:%S %p IST %Y") << endl;
          for(int ii=1;ii<=pidcounter;ii++){
            if(a[ii].iskill==0){
           for(auto it=a[ii].pagetable.begin();it!=a[ii].pagetable.end();it++){
           outpte<<ii<<" "<<it->first<<" "<<it->second<<" "<<a[ii].isinmain[it->first]<<endl;
              }
            }
          }
      }
      else if(command=="print"){
        string x;
        i >> x;
        int memloc=stoi(x);
        int pgno1=memloc/P;
        string y;
        i >> y;
        int length=stoi(y);
        int pgno2=(memloc+length-1)/P;
        for(int j=memloc;j<memloc+length;j++){
            out<<"Value of "<<j<<" : "<<mainmem[j]<<endl;
        }
        for(int j=pgno1;j<=pgno2;j++){
          lru.remove({j,mp[j].second});
           lru.push_front({j,mp[j].second});
        }
      }
      else if(command=="exit"){
         break;
      }
    }
}
