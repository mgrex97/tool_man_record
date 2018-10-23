#include<stdlib.h>
#include<stdio.h>

// 線段資料的儲存格式 (min,max)
typedef struct Segment{
    int min, max;
    // Link list: 與下個線段串接起來。
    struct Segment * next;
}segment;

// 預先宣告
void compare(segment **, int, int);

int main(){
    int segment_number=0, i=0, min, max, sum = 0;
    segment * head = NULL;

    // 有N 筆線段
    scanf("%d", &segment_number);

    // 讀入 N 筆開始端點座標值與結束端點座標
    for(i=0; i<segment_number; i++){
        scanf("%d %d", &min,&max);
        // 結束端點座標必須大於開始端點座標值 
        if(min < max){
            i--;
            printf("錯誤座標,重新輸入.");
            continue;
        }
        //送入遞迴中比較
        compare(&head,min,max); 
    }

    // 計算覆蓋長度
    while(head != NULL){
        sum += (head-> max - head->min);
        head = head->next;
    }

    // 顯示結果
    printf("線段覆蓋長度: %d\n", sum);

    return 1;
}

void compare(segment ** head,int min,int max){
    segment * temp = NULL;
    // 透過線段的比較找到 Link List 插入的點
    // 此條件代表找到插入的點
    if(*head == NULL | (*head)->min > max){
        // 開始插入
        temp = (segment *)malloc(sizeof(segment));
        temp->min = min;
        temp->max = max;
        temp->next = *head;
        *head = temp;
        return;
    // 還沒找到插入的點
    }else if((*head)->max < min){
        // 進入遞迴，對下一個線段做比較。
        compare(&((*head)->next),min,max);
        return;
    }
    // 確定 (mix,max) 與當前 head 所儲存的線段重疊

    if((*head)->min > min){
        (*head)->min = min;
    }

    if((*head)->max < max){
        (*head)->max = max;
    }
}
