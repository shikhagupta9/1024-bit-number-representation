#include<stdio.h>
#include<stdlib.h>
#include <string.h>
typedef struct Node_tag
{    int data;
    struct Node_tag *next;
}Node_type;

typedef struct bint_tag
{
    Node_type *start;
}bint;

Node_type* InsertAtStart(Node_type *list_ptr,int d)
{    Node_type *nptr;
    nptr=(Node_type*)malloc(sizeof(Node_type));
    nptr->data=d;
    nptr->next=list_ptr;
    list_ptr=nptr;
    return list_ptr;
}


Node_type* DeleteAtStart(Node_type *list_ptr,int *dptr)
{    Node_type *nptr;
    nptr=list_ptr;
    if(list_ptr!=NULL)
    {    list_ptr=list_ptr->next;
        *dptr=nptr->data;
        free(nptr);
    }
    return list_ptr;
}

void traverselist(Node_type *list_ptr)
{    Node_type *nptr;
    nptr=list_ptr;
    while(nptr!=NULL)
    {    printf("%d ",nptr->data);
        nptr=nptr->next;
    }
}

Node_type* InsertAtEnd(Node_type *list_ptr,int d)
{    Node_type *nptr,*ptr;
    nptr=(Node_type*)malloc(sizeof(Node_type));
    nptr->data=d;
    nptr->next=NULL;
    if(list_ptr==NULL)
    {    list_ptr=nptr;
    }
    else
    {    ptr=list_ptr;
        while(ptr->next!=NULL)
        {    ptr=ptr->next;
        }
        ptr->next=nptr;
    }
    return list_ptr;
}
Node_type* DeleteList(Node_type *list_ptr)
{    int data;
    while(list_ptr!=NULL)
    {    list_ptr=DeleteAtStart(list_ptr,&data);
    }
    return list_ptr;
}

int isgreater(char s1[],char s2[])
{
    int l1,l2,retval=0,flag=1,i=0;
    l1=strlen(s1);
    l2=strlen(s2);
    if (l1>l2)
    {
        retval=1;
    }else if(l2>l1)
    {
        retval=2;
    }else
    {
        
        while(flag==1&&i<l1)
        {
            if (s1[i]>s2[i])
            {
                retval=1;
                flag=0;
            }else if(s1[i]<s2[i])
            {
                retval=2;
                flag=0;
            }else
            {
                i++;
            }
        }
    }
    return retval;
}


bint getnum(char s[])
{
    bint n;
    n.start=NULL;
    int i=0,d=0;
    for (i=0;s[i]!='\0'; i++)
    {
        d=s[i]-'0';
        n.start=InsertAtStart(n.start, d);
    }
    return n;
}

void shownum(bint n)
{
    Node_type *trav=NULL,*p2;
    Node_type *ptr=n.start;
    if(ptr==NULL)
    {
        printf("0\n");
    }
    else
    {
        while (ptr)
        {
            trav=InsertAtStart(trav, ptr->data);
            ptr=ptr->next;
        }
        p2=trav;
        while (p2)
        {
            printf("%d",p2->data);
            p2=p2->next;
        }
        DeleteList(trav);

    }
    printf("\n");
   
}



bint addnum(bint n1,bint n2)
{
    Node_type *p1,*p2;
    int carry=0,d=0;
    bint res;
    res.start=NULL;
    p1=n1.start;
    p2=n2.start;
    while (p1&&p2)
    {
        d=p1->data+p2->data+carry;
        carry=d/10;
        d=d%10;
        res.start=InsertAtEnd(res.start, d);
        p1=p1->next;
        p2=p2->next;
    }
    while (p2!=NULL)
    {
        d=p2->data+carry;
        carry=d/10;
        d=d%10;
        res.start=InsertAtEnd(res.start, d);
        p2=p2->next;
    }
    while (p1!=NULL)
    {
        d=p1->data+carry;
        carry=d/10;
        d=d%10;
       
        res.start=InsertAtEnd(res.start, d);
        p1=p1->next;
    }
    if (carry!=0)
    {
        res.start=InsertAtEnd(res.start,carry);
    }
    
    return res;
    
}

bint subtract(bint n1,bint n2,int l)
{
    Node_type *p1,*p2,*p;
    int carry=0,big=0,small=0,dif=0;
    bint res;
    res.start=NULL;
    if(l==1)
    {
        p1=n1.start;
        p2=n2.start;
    }
    else if(l==2)
    {
        p1=n2.start;
        p2=n1.start;
    }else
    {
        return res;
    }
    while (p1&&p2)
    {
        big=p1->data;
        small=p2->data;
        if (small>(big-carry))
        {
            dif=10+big-small-carry;
            carry=1;
        }else
        {
            dif=big-small-carry;
            carry=0;
        }
        res.start=InsertAtStart(res.start, dif);
        p1=p1->next;
        p2=p2->next;
    }
    while (p1)
    {
        if (p1->data<carry)
        {
            dif=p1->data+10-carry;
            carry=1;
        }
        else
        {
            dif=p1->data-carry;
            carry=0;
        }
        res.start=InsertAtStart(res.start, dif);
        p1=p1->next;
    }
    p=res.start;
    while (p&&p->data==0) {
        p=p->next;
    }if (p==NULL) {
        printf("0\n");
    }
    while (p)
    {
        printf("%d",p->data);
        p=p->next;
    }printf("\n");

    return res;
    
}

bint mult(bint n1,bint n2)
{
    Node_type *p1,*p2,*p;
    int carry=0,d,count=0,i;
    bint res,temp;
    res.start=NULL;
    temp.start=NULL;
    p1=n1.start;
    p2=n2.start;
   
    while (p2)
    {
        if(p2->data!=0)
        {
            i=count;
            carry=0;
            for (i=count; i>0; i--)
            {
                temp.start=InsertAtEnd(temp.start, 0);
            }
            p1=n1.start;
            while (p1)
            {
                d=(p1->data)*(p2->data)+carry;
                carry=d/10;
                d=d%10;
                temp.start=InsertAtEnd(temp.start, d);
                p1=p1->next;
            }
            if (carry>0)
            {
                temp.start=InsertAtEnd(temp.start, carry);
            }
            res=addnum(res, temp);
            DeleteList(temp.start);
            temp.start=NULL;
        }
        
        count++;
        p2=p2->next;
    }
    DeleteList(temp.start);
    p=res.start;
    while (p&&p->data==0) {
        p=p->next;
    }

    return res;

}

int initialise(bint *n1,bint *n2,int *sign1,int *sign2)
{
  
    char s1[310],s2[310];
    int big;
    printf("enter the first number \n");
    scanf("%s",s1);
    *n1=getnum(&s1[1]);
    printf("enter the second number\n");
    scanf("%s",s2);
    *n2=getnum(&s2[1]);
    big=isgreater(&s1[1], &s2[1]);
    if (s1[0]=='+')
    {
        *sign1=1;
    }else
    {
        *sign1=0;
    }
    if (s2[0]=='+')
    {
        *sign2=1;
    }else
    {
        *sign2=0;
    }
    return big;
}


int main()
{
    bint num1,num2;
    int big,sign1,sign2;
    big=initialise(&num1, &num2,&sign1,&sign2);
    printf("first num is \n");
    shownum(num1);
    printf("second num is \n");
    shownum(num2);
    printf("addition is \n");
    if (sign2==sign1)
    {
        if (sign2==0) {
            printf("-");
        }
        shownum(addnum(num1, num2));
    }
    else if (sign1!=sign2)
    {
        if ((sign1==0&&big==1)||(sign2==0&&big==2))
        {
            printf("-");
        }
        subtract(num1, num2, big);
    }
    printf("subtraction \n");
    if (sign2==sign1)
    {
        if ((big==2&&sign2==1)||(big==1&&sign1==0))
        {
            printf("-");
        }
          subtract(num1, num2, big);
    }
    else if(sign2!=sign1)
    {
        if (sign1==0)
        {
            printf("-");
        }
        shownum(addnum(num1, num2));
    }
    printf("\n");
    printf("multiplication \n");
    if (sign2!=sign1)
    {
        printf("-");
       
    } shownum(mult(num1, num2));
    
    
    
    return 0;
}




















