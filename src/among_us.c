/***************************************************
 *                                                 *
 * file: among_us.c                                *
 *                                                 *
 * @Author  Antonios Peris                         *
 * @Version 20-10-2020                             *
 * @email   csdp1196@csd.uoc.gr                    *
 *                                                 *
 * @brief   Implementation of among_us.h           *
 *                                                 *
 ***************************************************
 */
 
#include "among_us.h"
 
/* Global variable, pointer to the head of the players list */
struct Players *players_head;

/* Global variable, pointer to the head of the tasks list */
struct Head_GL *tasks_head;

/* Global variable, pointer to the top of the completed task's stack */
struct Head_Completed_Task_Stack *tasks_stack;

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
 
 
    struct Tasks *tasks_sentinel;
int initialize() {
    players_head =(struct Players*)malloc(sizeof(struct Players));
    tasks_head=(struct Head_GL*)malloc(sizeof(struct Head_GL));
    tasks_sentinel=(struct Tasks*) malloc(sizeof(struct Tasks));
    tasks_stack=(struct Head_Completed_Task_Stack*)malloc(sizeof(struct Head_Completed_Task_Stack));
    tasks_head->head=NULL;
    tasks_sentinel->difficulty=-1;
    players_head->next=NULL;
    tasks_stack->count=0;
    tasks_stack->head=NULL;
    return 1;
}
 
/**
 * @brief Register player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
 
int register_player(int pid,int is_alien) {
    struct Tasks *last=(struct Tasks*)malloc(sizeof(struct Tasks));
    if(players_head->next==NULL){
        struct Players *players =(struct Players*)malloc(sizeof(struct Players));
        players->next=players_head;
        players_head->pid=-1;
        players_head->next=players;
        players_head->prev=players;
        players->prev=players_head;
        players->pid=pid;
        players->is_alien=is_alien;
        players->evidence=0;
        players->tasks_head=last;
        players->tasks_sentinel=last;
        last->tid=-1;
        last->difficulty=0;
        last->next=NULL;
    }else{
        struct Players *players =(struct Players*)malloc(sizeof(struct Players));
        players->next=players_head->next;
        players_head->next=players;
        players->prev=players_head;
        (players->next)->prev=players;
        players->pid=pid;
        players->is_alien=is_alien;
        players->evidence=0;
        players->tasks_head=last;
        players->tasks_sentinel=last;
        last->tid=-1;
        last->difficulty=0;
        last->next=NULL;
    }
    print_players();
    return 1;
}
 
/**
 * @brief Insert task in the general task list
 *
 * @param tid The task id
 * 
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_task(int tid,int difficulty) {
      if(tasks_head->head==NULL||(tasks_head->head)->difficulty>difficulty){   
        struct Tasks *task=(struct Tasks*)malloc(sizeof(struct Tasks));
        task->next=tasks_head->head;
        tasks_head->head=task;
        task->tid=tid;
        task->difficulty=difficulty;
        if(difficulty==1){
            tasks_head->tasks_count[0]=tasks_head->tasks_count[0]+1;
        }else if(difficulty==2){
            tasks_head->tasks_count[1]=tasks_head->tasks_count[1]+1;
        }else{
           tasks_head->tasks_count[2]=tasks_head->tasks_count[2]+1;
        }
    }else{
        struct Tasks* now=tasks_head->head; 
        struct Tasks* prev=NULL;
        while ( now!=NULL&&now->difficulty < difficulty) {
            prev=now; 
            now = now->next; 
        } 
        struct Tasks *task=(struct Tasks*)malloc(sizeof(struct Tasks));
        if(prev==NULL){
            task->next=now;
            tasks_head->head=task;
            task->tid=tid;
            task->difficulty=difficulty;
        }else{
            task->next = now;
            prev->next=task; 
            task->tid=tid;
            task->difficulty=difficulty;
        }
 
        if(difficulty==1){
            tasks_head->tasks_count[0]=tasks_head->tasks_count[0]+1;
        }else if(difficulty==2){
            tasks_head->tasks_count[1]=tasks_head->tasks_count[1]+1;
        }else{
           tasks_head->tasks_count[2]=tasks_head->tasks_count[2]+1;
        } 
    } 
    print_tasks();
    return 1;
} 
/**
 * @brief Distribute tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() {
 
    struct Tasks* nowT=tasks_head->head;
    struct Players* nowp=players_head;
    struct Tasks* newt;
    while(nowT!=NULL){
        nowp=nowp->next;
            while(nowp->is_alien==1||nowp->pid==-1){
            nowp=nowp->next;
            }
 
                if(nowp->tasks_sentinel->next!=NULL){
                    newt=(struct Tasks*)malloc(sizeof(struct Tasks));
                    nowp->tasks_sentinel->next->next=newt;
                    newt->next=nowp->tasks_sentinel;
                    nowp->tasks_sentinel->next=newt;
                }else{
                    newt=(struct Tasks*)malloc(sizeof(struct Tasks));
                    nowp->tasks_head=newt;
                    newt->next=nowp->tasks_sentinel;
                    nowp->tasks_sentinel->next=newt;
                }
            newt->tid=nowT->tid;
            newt->difficulty=nowT->difficulty; 
            nowT=nowT->next;
    }
    print_double_list();
    return 1;
}
 
/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param difficulty The task's difficuly
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int difficulty) {
    struct Tasks* tmp;
    struct Players* nowp=players_head->next;
    int flag=0;
    while(nowp->pid!=pid){
        nowp=nowp->next;
        if(nowp->pid==-1){
            flag=1;
            break;
        }
    }
    if(flag==1){
        printf("player not found\n");
    }else{

    
    struct Tasks *prev=nowp->tasks_head;
    struct Tasks* w=nowp->tasks_head;
    if(w!=nowp->tasks_sentinel){
        if(w->next==nowp->tasks_sentinel){
         tmp= (struct Tasks*)malloc(sizeof(struct Tasks));
        *tmp=*nowp->tasks_head;
        nowp->tasks_head=nowp->tasks_sentinel;
        nowp->tasks_sentinel->next=NULL;
        tmp->next=tasks_stack->head;
        tasks_stack->head=tmp;
        tasks_stack->count=tasks_stack->count+1;
        print_double_list();
    }else{
        int flag=0;
    while(w->difficulty!=difficulty){
        prev=w;
        w=w->next;
        flag=1;
        if(w->next==nowp->tasks_sentinel&&w->difficulty!=difficulty){
            tmp=(struct Tasks*)malloc(sizeof(struct Tasks));
            *tmp=*(nowp->tasks_head);
            nowp->tasks_head=nowp->tasks_head->next;
            //push
            tmp->next=tasks_stack->head;
            tasks_stack->head=tmp;
            tasks_stack->count=tasks_stack->count+1;
            print_double_list();
            break;
        }
    }
    if(w->difficulty==difficulty){
        if(prev==nowp->tasks_head&&flag==0){
           tmp=(struct Tasks*)malloc(sizeof(struct Tasks));
            *tmp=*w;
            nowp->tasks_head=nowp->tasks_head->next;
            //push
            tmp->next=tasks_stack->head;
            tasks_stack->head=tmp;
            tasks_stack->count=tasks_stack->count+1;
            print_double_list();
        }else{
            tmp=(struct Tasks*)malloc(sizeof(struct Tasks));
            *tmp=*w;
            prev->next=w->next;
            w->next=NULL;
            //push
            tmp->next=tasks_stack->head;
            tasks_stack->head=tmp;
            tasks_stack->count=tasks_stack->count+1;
            print_double_list();
        }
    }
    }
    }else{
        printf("player %d has no tasks\n",nowp->pid);
    }
    
    
    }
 
    return 1;
}
 
/**
 * @brief Eject Player
 * 
 * @param pid The ejected player's id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid) {
    int prevc=90;
    struct Players* nowp=players_head->next;
    struct Players* min;
    int tasksc;
    struct Tasks* nowt;
    if(nowp->pid==-1){
        return 0;
    }
    while(nowp->pid!=-1){
        if(nowp->pid!=pid&&nowp->is_alien!=1){
            nowt=nowp->tasks_head;
            tasksc=0;
            while(nowt!=nowp->tasks_sentinel){
                tasksc++;
                nowt=nowt->next;
            }
            if(tasksc<prevc){
               min=nowp;
               prevc=tasksc;
            }
            
        }
        nowp=nowp->next;
    }
    nowp=players_head->next;
while(nowp->pid!=pid){
    nowp=nowp->next;
    if(nowp->pid==-1){
        return 0;
    } 
}

nowp->prev->next=nowp->next;
nowp->next->prev=nowp->prev;
if(nowp->tasks_head->tid==-1){
    print_double_list();
    return 1;
}
if(min->tasks_head->tid==-1){
    min->tasks_head=nowp->tasks_head;
    min->tasks_sentinel=nowp->tasks_sentinel;
}else{
    struct Tasks* mintasks=min->tasks_head;
    struct Tasks * nowptasks=nowp->tasks_head;
    struct Tasks * prev=mintasks;
    struct Tasks *tmp;
    if(mintasks->difficulty>nowptasks->difficulty){
        tmp=nowptasks->next;
        nowptasks->next=mintasks;
        min->tasks_head=nowptasks;
        prev=nowptasks;
        nowptasks=tmp;
    }
    while(mintasks->tid!=-1){
        while(mintasks->difficulty>nowptasks->difficulty&&nowptasks->tid!=-1){
            tmp=nowptasks->next;
            nowptasks->next=mintasks;
            prev->next=nowptasks;
            prev=prev->next;
                nowptasks=tmp;

            
        }
        prev=mintasks;
        mintasks=mintasks->next;
        if(mintasks->tid==-1&&nowptasks->tid!=-1){
                prev->next=nowptasks;
                min->tasks_sentinel=nowp->tasks_sentinel;
                break;
        }
    }
}
 print_double_list();
    return 1;
}
 
/**
 * @brief Witness Eject Player
 *
 * @param pid_a The alien's pid
 * 
 * @param pid The crewmate's pid
 * 
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid, int pid_a, int number_of_witnesses){
    int prevc=90;
    struct Players* nowp=players_head->next;
    struct Players* min;
    int tasksc;
    struct Tasks* nowt;
    while(nowp->pid!=-1){
        if(nowp->pid!=pid&&nowp->is_alien!=1){
            nowt=nowp->tasks_head;
            tasksc=0;
            while(nowt!=nowp->tasks_sentinel){
                tasksc++;
                nowt=nowt->next;
            }
            if(tasksc<prevc){
               min=nowp;
               prevc=tasksc;
            }
            
        }
        nowp=nowp->next;
    }
    nowp=players_head->next;
while(nowp->pid!=pid){
    nowp=nowp->next;
    if(nowp->pid==-1){
        return 0;
    } 
}
nowp->prev->next=nowp->next;
nowp->next->prev=nowp->prev;
if(nowp->tasks_head->tid==-1){
    nowp=players_head->next;
    while(nowp->pid!=pid_a){
        nowp=nowp->next;
    }
    nowp->evidence=nowp->evidence+number_of_witnesses;
    print_double_list();
    return 1;
}
if(min->tasks_head->tid==-1){
    min->tasks_head=nowp->tasks_head;
    min->tasks_sentinel=nowp->tasks_sentinel;
}else{
    struct Tasks * mintasks=min->tasks_head;
    struct Tasks * nowptasks=nowp->tasks_head;
    struct Tasks * prev=mintasks;
    struct Tasks * tmp;
    if(mintasks->difficulty>nowptasks->difficulty){
        tmp=nowptasks->next;
        nowptasks->next=mintasks;
        min->tasks_head=nowptasks;
        prev=nowptasks;
        nowptasks=tmp;
    }
    while(mintasks->tid!=-1){
        while(mintasks->difficulty>nowptasks->difficulty&&nowptasks->tid!=-1){
            tmp=nowptasks->next;
            nowptasks->next=mintasks;
            prev->next=nowptasks;
            prev=prev->next;
            nowptasks=tmp;
        }
        prev=mintasks;
        mintasks=mintasks->next;
        if(mintasks->tid==-1&&nowptasks->tid!=-1){
                prev->next=nowptasks;
                min->tasks_sentinel=nowp->tasks_sentinel;
                break;
        }
    }
}
nowp=players_head->next;
while(nowp->pid!=pid_a){
    nowp=nowp->next;
}
nowp->evidence=nowp->evidence+number_of_witnesses;
 print_double_list();
    return 1;
}
 
 
/**
 * @brief Sabbotage
 *
 * @param pid The player's id
 *
 * @param number_of_tasks The number of tasks to be popped
 * 
 * @return 1 on success
 *         0 on failure
 */
int sabbotage(int pid, int number_of_tasks) {
    struct Players* nowp=players_head->next;
    while(nowp->pid!=pid){
        nowp=nowp->next;
        if(nowp->pid==-1){
            return 0;
        }
    }
    int c=0;
    int i=0;
    struct Tasks* nowt=tasks_stack->head;
    struct Tasks* nowptask;
    struct Tasks* prev;
    while(c<number_of_tasks){
        for(i=0;i<number_of_tasks/2;i++){
            nowp=nowp->prev;
        }
        while(nowp->is_alien==1||nowp->pid==-1){
            nowp=nowp->next;
        }
        
         nowptask=nowp->tasks_head;
        if(nowptask->tid==-1||nowptask->difficulty>=nowt->difficulty){
            
            tasks_stack->head=tasks_stack->head->next;
            tasks_stack->count=tasks_stack->count-1;
            nowt->next=nowptask;
            nowp->tasks_head=nowt;
            nowt=tasks_stack->head;
        }else{
            while(nowptask->difficulty<nowt->difficulty){
                prev=nowptask;
                nowptask=nowptask->next;
                if(nowptask->tid==-1){
                    break;
                }
            }
            tasks_stack->head=tasks_stack->head->next;
            tasks_stack->count=tasks_stack->count-1;
            nowt->next=nowptask;
            prev->next=nowt;
            nowt=tasks_stack->head;
            
        }
        c++;
    
    
   
    }
     print_double_list();
    return 1;
}
 
 
/**
 * @brief Vote
 *
 * @param pid The player's id
 * 
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid, int vote_evidence) {
    struct Players* nowp=players_head->next;
while(nowp->pid!=pid){
    nowp=nowp->next;
}
nowp->evidence=nowp->evidence+vote_evidence;

nowp=players_head->next;
int max=nowp->evidence;
struct Players* maxplayer=nowp;

while(nowp!=players_head){
    nowp=nowp->next;
    if(nowp!=players_head){
        if(max<nowp->evidence){
            maxplayer=nowp;
            max=nowp->evidence;
        }
    }
}
maxplayer->prev->next=maxplayer->next;
maxplayer->next->prev=maxplayer->prev;
    int prevc=90;
    nowp=players_head->next;
    struct Players* min;
    int tasksc;
    struct Tasks* nowt;
    while(nowp->pid!=-1){
        if(nowp->pid!=pid&&nowp->is_alien!=1){
             nowt=nowp->tasks_head;
            tasksc=0;
            while(nowt!=nowp->tasks_sentinel){
                tasksc++;
                nowt=nowt->next;
            }
            if(tasksc<prevc){
               min=nowp;
               prevc=tasksc;
            }
            
        }
        nowp=nowp->next;
    }
    if(min->tasks_head->tid==-1){
    min->tasks_head=maxplayer->tasks_head;
    min->tasks_sentinel=maxplayer->tasks_sentinel;
}else{
    struct Tasks* mintasks=min->tasks_head;
    struct Tasks * nowptasks=maxplayer->tasks_head;
    struct Tasks * prev=mintasks;
    struct Tasks *tmp;
    if(mintasks->difficulty>nowptasks->difficulty){
        tmp=nowptasks->next;
        nowptasks->next=mintasks;
        min->tasks_head=nowptasks;
        prev=nowptasks;
        nowptasks=tmp;
    }
    while(mintasks->tid!=-1){
        while(mintasks->difficulty>nowptasks->difficulty&&nowptasks->tid!=-1){
            tmp=nowptasks->next;
            nowptasks->next=mintasks;
            prev->next=nowptasks;
            prev=prev->next;
                nowptasks=tmp;

            
        }
        prev=mintasks;
        mintasks=mintasks->next;
        if(mintasks->tid==-1&&nowptasks->tid!=-1){
                prev->next=nowptasks;
                min->tasks_sentinel=maxplayer->tasks_sentinel;
                break;
        }
    }
}
 print_double_list();
    return 1;
}
 
 
/**
 * @brief Give Away Work
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work() {
    int prevc=90;
    struct Players* nowp=players_head->next;
    struct Players* min;
    int tasksc;
    struct Tasks* nowt;
    while(nowp->pid!=-1){
        if(nowp->is_alien!=1){
            nowt=nowp->tasks_head;
            tasksc=0;
            while(nowt!=nowp->tasks_sentinel){
                tasksc++;
                nowt=nowt->next;
            }
            if(tasksc<prevc){
               min=nowp;
               prevc=tasksc;
            }
            
        }
        nowp=nowp->next;
    }
    nowp=players_head->next;
    struct Players* max;
    prevc=-1;
    while(nowp->pid!=-1){
        if(nowp->is_alien!=1){
            nowt=nowp->tasks_head;
            tasksc=0;
            while(nowt!=nowp->tasks_sentinel){
                tasksc++;
                nowt=nowt->next;
            }
            if(tasksc>prevc){
               max=nowp;
               prevc=tasksc;
            }
            
        }
        nowp=nowp->next;
    }
    int halftasks=prevc/2;
    struct Tasks * maxtasks=max->tasks_head;
    if(min->tasks_head->tid==-1){
        int c=0;
        while(c!=halftasks){
            maxtasks=maxtasks->next;
            c++ ;
        }
        struct Tasks * maxtaskshead=max->tasks_head;
        max->tasks_head=maxtasks->next;
        maxtasks->next=min->tasks_sentinel;
        min->tasks_head=maxtaskshead;
        min->tasks_sentinel->next=maxtasks;
    
    }else{
        int c=0;
        while(c!=halftasks){
            maxtasks=maxtasks->next;
            c++ ;
        }
    }
print_double_list();
    return 1;
}
 
/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int terminate() {
    int humans=0;
    int aliens=0;
    struct Players *nowp=players_head->next;
    while (nowp->pid!=-1){
        if(nowp->is_alien==1){
            aliens++;
        }else{
            humans++;
        }
        nowp=nowp->next;
    }
    int c=0;
    struct Players* now=players_head->next;
    int tasks=0;
    while(c!=1){
        if(now->pid==-1){
            c++;
        }
 
        if(c!=1){
            tasks++;
        }else{
            printf("\n");
        }
        now=now->next;
    }
    if(aliens>humans){
        printf("Aliens win.\n");
        return 1;
    }else if(aliens==0||tasks_stack->count==tasks){
        printf("Crewmates win.\n");
        return 1;
    }else{
        return 0;
    }
    
}
 
/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players() {
    int c=0;
    struct Players* now=players_head->next;
    printf("Players= ");
    while(c!=1){
        if(now->pid==-1){
            c++;
        }
 
        if(c!=1){
            printf("<%d:%d> ", now->pid,now->is_alien);
        }else{
            printf("\n");
        }
        now=now->next;
    }
    return 1;
}
 
/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks() {
    struct Tasks* now=tasks_head->head;
     printf("List_Tasks = ");
    while(now!=NULL){
        printf("<%d:%d>",now->tid,now->difficulty);
        now=now->next;
    }
    printf("\n");
    return 1;
}
 
/**
 * @brief Print Stack
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stack() {
    struct Tasks * nowt=tasks_stack->head;
    printf("Stack_Tasks = ");
 while(nowt!=NULL){
    printf("<%d:%d>",nowt->tid,nowt->difficulty);
    nowt=nowt->next;
 }
 printf("\n");
    return 1;
}
 
/**
 * @brief Print Players & Task List
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_list() {
    int c=0;
    struct Players* nowp=players_head->next;
    while(c!=1){
        if(nowp->pid==-1){
            c++;
        }else{
            printf("player %d = ", nowp->pid);
            struct Tasks *nowT=nowp->tasks_head;
            if(nowp->is_alien==1){
                printf("he is alien \n");
            }else if(nowp->tasks_head==nowp->tasks_sentinel){
                printf("no tasks \n");
            }else{
                while(nowT!=nowp->tasks_sentinel){
                    printf("<%d:%d>",nowT->tid,nowT->difficulty);
                    nowT=nowT->next;
                }
                printf("\n");
            }
            nowp=nowp->next;
        }
    }
    return 1;
}
 
/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
 
int free_all(void) {
    return 1;
}
 