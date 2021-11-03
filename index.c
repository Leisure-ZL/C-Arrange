  #include<stdio.h>
  #include<stdlib.h>
  #include<string.h>
  
  #define TEANUM 20		//教师人数 
  #define STUNUM 5		//班级个数 
  #define ROOMNUM 5		//教室个数 
  
  /////////////////////数据设计/////////////////
  
  //教师信息存储 
  struct teacher_data{
  	int ID;						//教师ID 
  	char name[10];				//教师名字 
  	struct{ 		
  		int stuID;				//任课班级ID 
  		char Class[10];			//课程名称 
  		char ClassGrade[10];	//任教班级名称 
	  }classArr[15];			//任教课程数 
	struct{
		int spare;
	}timeArr[12][5];			//记录该时间段是否空闲 
  }tea[TEANUM]; 
  
  
  //学生信息存储 
  struct student_data{
  	int ID;
  	char ClassGrade[10];			//班级名称 
  	struct{
  		int spare;					//空余情况(1/0) 
  		char Class[10];				//课程名字 
  		int teaID;					//教师ID 
  		int time;					//课程总课时 
  		int weekClaNum[2];			//每周课程段    存储int 
	  }classArr[15];				//上限15门课 
  }stu[STUNUM]; 
  
  
   //教室信息存储 
  struct classroom_data{
   	int ID;						//教室编号 
	struct{
		int spare;				//空余情况（1/0）
		char Class[10];			//课程名称 
		int teaID;				//教师ID 
		char ClassGrade[10];	//班级名称		
	}timeArr[12][5];			//课程时间段
   }cla[ROOMNUM]; 
   
  
  //班级课表存储
  struct classList{
  	int ID;
  	char ClassGrade[10];		//班级名称 
  	struct{
  		char Class[10];			//课程名称 
	  }timeArr[12][5];
  }claList[STUNUM]; 
  

  //教师课表存储
  struct teacherList{
  	int ID;
  	char name[10];
  	struct{
  		int spare;
  		char Class[10];			//课程名称 
  		char ClassGrade[10];	//任教班级名称 
	  }timeArr[12][5];
  }teaList[TEANUM]; 
  
  
  ///////////////////函数设计//////////////////// 
  
  ///////////教师端： 
  
//教师信息录入 
  void teacher_input(int teaNum,char path[20]){
  	int i=0;
	int flag = 1;
	FILE *fp;
	fp = fopen(path,"w");
	if (NULL == fp){				 
    	printf ("Failed to open the file !\n");
	}
  	printf("请输入ID,name:\n");
  	scanf("%d%s",&tea[teaNum].ID,&tea[teaNum].name);
  	fprintf(fp,"%d\t%s\n",tea[teaNum].ID,tea[teaNum].name);
  	while(flag){
  		printf("请输入课程与班级及其ID:\n");
  		scanf("%s%s%d",&tea[teaNum].classArr[i].Class,&tea[teaNum].classArr[i].ClassGrade,&tea[teaNum].classArr[i].stuID);
  		fprintf(fp,"%s %s %d\n",tea[teaNum].classArr[i].Class,tea[teaNum].classArr[i].ClassGrade,tea[teaNum].classArr[i].stuID);
  		printf("是否继续录入（1/0）：");
		scanf("%d",&flag); 
		i++;
	  }
	  fclose(fp);
  } 
  
//教师信息输出 
  void teacher_output(int teaNum,char path[20]){
  	int i=0;
  	FILE *fp;
  	fp = fopen(path,"r");
  	if (NULL==fp) {
    	printf ("Failed to open the file !\n");
    	exit(0);
	}
  	printf("老师您好！\n"); 
  	fscanf(fp,"%d\t%s\n",&tea[teaNum].ID,&tea[teaNum].name);
  	printf("ID:%d\nname:%s\n",tea[teaNum].ID,tea[teaNum].name);
  	while(tea[teaNum].classArr[i].Class[0] != '\0' || !feof(fp)){
  		fscanf(fp,"%s %s %d",&tea[teaNum].classArr[i].Class,&tea[teaNum].classArr[i].ClassGrade,&tea[teaNum].classArr[i].stuID);
  		printf("sub:%8s class:%8s stuID:%d\n",tea[teaNum].classArr[i].Class,tea[teaNum].classArr[i].ClassGrade,tea[teaNum].classArr[i].stuID);
  		i++;
  	}
  	fclose(fp);
  	printf("------------------------------------\n");
  }
   
//教师初始化 
  void teacher_init(){
  	int i,j,m,n;
  	for(i=0;i<TEANUM;i++){
  		  	for(m=0;m<12;m++){
  		  		for(n=0;n<5;n++){
  		  			tea[i].timeArr[m][n].spare = 1;	
			}
		}	
	  }
  }
  
//教师调课
  
  	//单课时间调节 
void teacherSet(int ID,int day,int time){
	tea[ID].timeArr[time-1][day-1].spare = 0;
} 

	//时间段调节 
void teacherSetPeriod(int ID,int x){//x=0:上午   x=1:下午   x=2:晚上 
	int i,j;
	if(!x){//上午 
		for(i=0;i<5;i++){
			for(j=0;j<5;j++){
				tea[ID].timeArr[j][i].spare = 0;			
			}
		}	
	}
	if(x){//下午 
		for(i=0;i<5;i++){
			for(j=5;j<9;j++){
				tea[ID].timeArr[j][i].spare = 0;			
			}
		}
	}
	if(x == 2){//晚上 
		for(i=0;i<5;i++){
			for(j=9;j<12;j++){
				tea[ID].timeArr[j][i].spare = 0;			
			}
		}
	}
}

//教师调课for user(交互式)
void teacherSetForUser(){
	int id,day,time;
	printf("请输入您的ID:\n");
	scanf("%d",&id);
	printf("%s老师您好！请输入您需要调休的时间(1-5 & 1-12)\n",tea[id].name);
	scanf("%d %d",&day,&time);
	tea[id].timeArr[time-1][day-1].spare = 0;
	printf("succeed!\n");
} 



//教师课表输出
void teacherList_output(int teaNum,char path[20]){
	int i,j,k;
	FILE *fp;
	fp = fopen(path,"w");
	printf("ID:%d\t教师:%s\n",tea[teaNum].ID,tea[teaNum].name);
	fprintf(fp,"ID:%d\t教师:%s\n",tea[teaNum].ID,tea[teaNum].name);
	for(i=0;i<12;i++){
		for(j=0;j<5;j++){
			printf("class:%8s course:%8s | ",teaList[teaNum].timeArr[i][j].Class,teaList[teaNum].timeArr[i][j].ClassGrade);
			fprintf(fp,"class:%10s course:%10s | ",teaList[teaNum].timeArr[i][j].Class,teaList[teaNum].timeArr[i][j].ClassGrade);
		}
		printf("\n");
		fprintf(fp,"\n");
		if(i==4 || i==8){
			printf("\n");
			fprintf(fp,"\n");				
		}
	} 
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
} 
  
  
  
  //////////////学生端：
  
//学生信息录入(写入文件student_data.txt)
  void student_input(int stuNum,char path[20]){
  	int i=0;
  	int flag=1;
  	FILE *fp1;
  	fp1=fopen(path,"w");
  	if (NULL == fp1){				 //以返回值fpl判断是否存在 
    	printf ("Failed to open the file !\n");
	}
  	printf("请输入ID，班级:\n");
  	scanf("%d%s",&stu[stuNum].ID,&stu[stuNum].ClassGrade);
  	fprintf(fp1,"%d\t%s\n",stu[stuNum].ID,stu[stuNum].ClassGrade);//向文件输入 
  	while(flag){
  		printf("请输入课程,任教教师ID与学时:\n");
  		scanf("%s%d%d",&stu[stuNum].classArr[i].Class,&stu[stuNum].classArr[i].teaID,&stu[stuNum].classArr[i].time);
  		if(stu[stuNum].classArr[i].time > 54){//如果大于54课时，每周课大于3节，分成两次上课 
  			stu[stuNum].classArr[i].weekClaNum[0] = stu[stuNum].classArr[i].time / 18 / 2;
 			stu[stuNum].classArr[i].weekClaNum[1] = stu[stuNum].classArr[i].time / 18 - stu[stuNum].classArr[i].weekClaNum[0];
		  }else{
		  	stu[stuNum].classArr[i].weekClaNum[0] = stu[stuNum].classArr[i].time / 18;
		  	stu[stuNum].classArr[i].weekClaNum[1] = 0;
		  }
  		fprintf(fp1,"%s %d %d %d %d\n",stu[stuNum].classArr[i].Class,stu[stuNum].classArr[i].teaID,stu[stuNum].classArr[i].time,stu[stuNum].classArr[i].weekClaNum[0],
		stu[stuNum].classArr[i].weekClaNum[1]);
  		printf("是否继续录入（1/0）：");
		scanf("%d",&flag);
		i++;
	  }
	  fclose(fp1);
  } 
  
  
//学生信息输出(从文件中读取并存储)
  void student_output(int stuNum,char path[30]){
  	int i=0;
  	FILE *fp;
  	fp=fopen(path,"r");
  	if (NULL==fp) {
    	printf ("Failed to open the file !\n");
    	exit(0);
	}
  	fscanf(fp,"%d	%s\n",&stu[stuNum].ID,&stu[stuNum].ClassGrade);
  	printf("ID:%d\nclass:%s\n",stu[stuNum].ID,stu[stuNum].ClassGrade);
  	while(stu[stuNum].classArr[i].Class[0] != '\0' || !feof(fp)){//feof判断是否读取结束 
		fscanf(fp,"%s %d %d %d %d ",&stu[stuNum].classArr[i].Class,&stu[stuNum].classArr[i].teaID,&stu[stuNum].classArr[i].time,&stu[stuNum].classArr[i].weekClaNum[0],
			&stu[stuNum].classArr[i].weekClaNum[1]);
		printf("sub:%8s teaID:%d spare:%d time:%d weektime:%d\n",stu[stuNum].classArr[i].Class,stu[stuNum].classArr[i].teaID,stu[stuNum].classArr[i].spare,
		  stu[stuNum].classArr[i].time,stu[stuNum].classArr[i].weekClaNum[1]);
  		i++;
  } 
  fclose(fp);
  printf("------------------------------------------------\n");
}

//班级初始化
  void class_init(int stuNum){
  	int i;
  	for(i=0;i<15;i++){
  		stu[stuNum].classArr[i].spare = 1;
	  }
	}
	
	
//班级课表输出
void class_output(int stuNum,char path[20]){
	int i,j,k;
	FILE *fp;
	fp = fopen(path,"w");
	printf("班级:%s\n",stu[stuNum].ClassGrade);
	fprintf(fp,"班级:%s\n",stu[stuNum].ClassGrade);
	for(i=0;i<12;i++){
		for(j=0;j<5;j++){
			printf("class:%8s course:%8s | ",claList[stuNum].ClassGrade,claList[stuNum].timeArr[i][j].Class);
			fprintf(fp,"class:%10s course:%10s | ",claList[stuNum].ClassGrade,claList[stuNum].timeArr[i][j].Class);
		}
		printf("\n");
		fprintf(fp,"\n");
		if(i==4 || i==8){
			printf("\n");
			fprintf(fp,"\n");				
		}
	}
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
} 


////////////教室

//教室初始化
  void classroom_init(){//将所有时间段教室spare置为1 
  	int i,k,j;
  	for(i=0;i<ROOMNUM;i++){
  		cla[i].ID = i + 1;
  		for(j=0;j<12;j++)
  			for(k=0;k<5;k++){
  				cla[i].timeArr[j][k].spare=1;
			  }
	  }
  } 
  
//教室信息输出
void classroom_output(){
	int i,j,k,x;
	FILE *fp;
	fp=fopen("classroom_data.txt","w");
	if (NULL==fp) 
	{
    	printf ("Failed to open the file !\n");
    	exit (0) ; 
		}
	for(i=0;i<ROOMNUM;i++){
		printf("教室:%d\n",cla[i].ID);
		fprintf(fp,"教室:%d\n",cla[i].ID);
		for(j=0;j<12;j++){
			for(k=0;k<5;k++){
				printf("class:%8s coures:%8s | ",cla[i].timeArr[j][k].ClassGrade,cla[i].timeArr[j][k].Class);
				fprintf(fp,"class:%8s coures:%8s | ",cla[i].timeArr[j][k].ClassGrade,cla[i].timeArr[j][k].Class);
			}
			printf("\n");
			fprintf(fp,"\n");
			if(j==4 || j==8){
				printf("\n");
				fprintf(fp,"\n");				
			}

		}
		printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fp,"\n*******************************************************************************\n");
	}
	fclose(fp);
} 


  ////////////排课 
 
//排课
 void arrange(){
 	int i,j,k,x,y,z,t,m,n=0;
 	int teaID;
 	for(x=0;x<STUNUM;x++){					//班级 	
 		for(t=0;t<2;t++){					//每周两次课程 
 			class_init(x);					//初始化课程spare=1; 
		 	for(y=0;y<15;y++){				//课程 
		  		for(i=0;i<ROOMNUM;i++){		//教室数 
		 			for(j=0;j<5;j++){		//天数 
		 				for(k=0;k<12;k++){	//每天时间段 
		 					teaID = stu[x].classArr[y].teaID;	//记录该课程教师ID	 					
			 				if(k <= 4){				//上午5节 	1~5
			 					if(cla[i].timeArr[k][j].spare && stu[x].classArr[y].spare && tea[teaID].timeArr[k][j].spare && 5-k >= stu[x].classArr[y].weekClaNum[t] ){
			 						for(z=k;z<stu[x].classArr[y].weekClaNum[t]+k;z++){
			 							cla[i].timeArr[z][j].spare = 0;
			 							tea[teaID].timeArr[k][j].spare = 0;
			 							teaList[teaID].timeArr[z][j].spare = 0;
			 							strcpy(cla[i].timeArr[z][j].Class,stu[x].classArr[y].Class);	//课程名称传入教室信息 
			 							strcpy(cla[i].timeArr[z][j].ClassGrade,stu[x].ClassGrade);		//班级名称传入教室信息
										strcpy(claList[x].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);//信息存入班级课表 
										strcpy(claList[x].ClassGrade,cla[i].timeArr[z][j].ClassGrade);
										teaList[teaID].ID = tea[teaID].ID;								//信息存入教师课表 
										strcpy(teaList[teaID].name,tea[teaID].name);
										strcpy(teaList[teaID].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);
										strcpy(teaList[teaID].timeArr[z][j].ClassGrade,stu[x].ClassGrade);
									 }
			 						stu[x].classArr[y].spare = 0;
							 	}
							 }
							if(k>4 && k<9){		//下午4节 	6~9
								if(cla[i].timeArr[k][j].spare && stu[x].classArr[y].spare && tea[teaID].timeArr[k][j].spare && 9-k-stu[x].classArr[y].weekClaNum[t] >= 0){
			 						for(z=k;z<stu[x].classArr[y].weekClaNum[t]+k;z++){
			 							cla[i].timeArr[z][j].spare = 0;
			 							tea[teaID].timeArr[k][j].spare = 0;
			 							teaList[teaID].timeArr[z][j].spare = 0;
			 							strcpy(cla[i].timeArr[z][j].Class,stu[x].classArr[y].Class);
			 							strcpy(cla[i].timeArr[z][j].ClassGrade,stu[x].ClassGrade);
			 							strcpy(claList[x].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);
										strcpy(claList[x].ClassGrade,cla[i].timeArr[z][j].ClassGrade);
										teaList[teaID].ID = tea[teaID].ID;		//存入教师课表 
										strcpy(teaList[teaID].name,tea[teaID].name);
										strcpy(teaList[teaID].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);
										strcpy(teaList[teaID].timeArr[z][j].ClassGrade,stu[x].ClassGrade);
									 }
			 						stu[x].classArr[y].spare = 0;
							 	}
							}
							if(k>8){				//晚上4节 	10~12
								if(cla[i].timeArr[k][j].spare && stu[x].classArr[y].spare && tea[teaID].timeArr[k][j].spare && 12-k-stu[x].classArr[y].weekClaNum[t] >= 0){
			 						for(z=k;z<stu[x].classArr[y].weekClaNum[t]+k;z++){
			 							cla[i].timeArr[z][j].spare = 0;
			 							tea[teaID].timeArr[k][j].spare = 0;
			 							strcpy(cla[i].timeArr[z][j].Class,stu[x].classArr[y].Class);
			 							strcpy(cla[i].timeArr[z][j].ClassGrade,stu[x].ClassGrade);
			 							strcpy(claList[x].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);
										strcpy(claList[x].ClassGrade,cla[i].timeArr[z][j].ClassGrade);
										teaList[teaID].ID = tea[teaID].ID;//存入教师课表 
										strcpy(teaList[teaID].name,tea[teaID].name);
										strcpy(teaList[teaID].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);
										strcpy(teaList[teaID].timeArr[z][j].ClassGrade,stu[x].ClassGrade);
										teaList[teaID].timeArr[z][j].spare = 0;
									 }
			 						stu[x].classArr[y].spare = 0;
							 	}
							}
						 }
					}
			 	}		
			 }
		}
	 }
 } 
 
 
   
   ///////////功能入口///////////////// 
   void teacher_input(int teaNum,char path[20]); 		//教师信息录入(控制台输入，存储并写入文件) 
   void teacher_output(int teaNum,char path[20]);		//教师信息输出(读取文件存入内存) 
   void teacher_init();									//教师初始化
   void teacherSet(int ID,int day,int time);			//单课时间调休  day:星期  time:时间段 
   void teacherSetPeriod(int ID,int x);					//时间段调休    x=0:上午   x=1:下午   x=2:晚上 
   void teacherSetForUser();							//交互式单课调休
   void teacherList_output(int teaNum,char path[20]);	//教师课表输出
   void student_input(int stuNum,char path[20]);		//学生信息录入
   void student_output(int stuNum,char path[30]);		//学生信息输出
   void class_init(int stuNum);							//班级初始化
   void class_output(int stuNum,char path[20]);			//班级课表输出
   void classroom_init();								//教室初始化
   void classroom_output();								//教室信息输出
   void arrange();										//排课主算法 
    
    
   					
  //////////////////主程序入口///////////////// 
  int main(){

//	student_input(5,"./student/student_data_5.txt");
//	teacher_input(14,"./teacher/teacher_data_14.txt");
   	student_output(0,"./student/student_data_0.txt");
  	student_output(1,"./student/student_data_1.txt");
   	student_output(2,"./student/student_data_2.txt");
   	student_output(3,"./student/student_data_3.txt");
   	student_output(4,"./student/student_data_4.txt");
  	teacher_output(0,"./teacher/teacher_data_0.txt");
	teacher_output(1,"./teacher/teacher_data_1.txt");
	teacher_output(2,"./teacher/teacher_data_2.txt");
	teacher_output(3,"./teacher/teacher_data_3.txt");
	teacher_output(4,"./teacher/teacher_data_4.txt");
	teacher_output(5,"./teacher/teacher_data_5.txt");
	teacher_output(6,"./teacher/teacher_data_6.txt");
	teacher_output(7,"./teacher/teacher_data_7.txt");
	teacher_output(8,"./teacher/teacher_data_8.txt");
	teacher_output(9,"./teacher/teacher_data_9.txt");
	teacher_output(10,"./teacher/teacher_data_10.txt");
	teacher_output(11,"./teacher/teacher_data_11.txt");
	teacher_output(12,"./teacher/teacher_data_12.txt");
	teacher_output(13,"./teacher/teacher_data_13.txt");
	teacher_output(14,"./teacher/teacher_data_14.txt");
   	
   	teacher_init();
  	classroom_init();
//	teacherSet(0,1,1);
//	teacherSet(0,1,2);
//  teacherSet(0,1,3);
//	teacherSetPeriod(0,1);
//	teacherSetForUser();
  	arrange();
  	
	classroom_output();
  	class_output(0,"./class/class_data_0.txt");
  	class_output(1,"./class/class_data_1.txt");
  	class_output(2,"./class/class_data_2.txt");
  	class_output(3,"./class/class_data_3.txt");
  	class_output(4,"./class/class_data_4.txt");

  	teacherList_output(0,"./teacher/teacherList_0.txt");
  	teacherList_output(1,"./teacher/teacherList_1.txt");
  	teacherList_output(2,"./teacher/teacherList_2.txt");
  	teacherList_output(3,"./teacher/teacherList_3.txt");

  	return 0;
  }
  
  
  
  
  
