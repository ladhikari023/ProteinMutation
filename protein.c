/* 
 Laxman Adhikari
 CS 241L

 In this program, I have used linked list to store the character letter which represent the 
 Amino acid which is given in the file spike.in. After storing the data as a linked list, I 
 handled the command line arguments. For that, I have used if/else where if would identify if
 the argument is for deletion or swap. Then, the respective function of deletion and mutation
 are called and they are responsible for changing the data in the linked list. After processing
 all the command line arguments, the updated linked list is printed with the help of 
 write_output function. The command line argument can be anything as long as it is valid because
 I didn't use the error handler. 

*/ 


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct aminostr {
   char aminochar;
   int position;
   struct aminostr *next;
};


/* Read from input, and create the linked list */
int load_data(struct aminostr **head)
{
   char buffer[100];
   struct aminostr *current = NULL;
   struct aminostr *newnode = NULL;
   int idx, total=0;

   while (1) {
      if (fgets(buffer, 100, stdin) == NULL) break;

      buffer[strcspn(buffer, "\r\n")] = '\0';

      idx = 0;
      while (buffer[idx] != 0) {
         newnode = (struct aminostr *) malloc (sizeof (struct aminostr));
         newnode->next = NULL;
         newnode->aminochar = buffer[idx++];
         newnode->position = total + 1;
         total++;

         if (current == NULL) current = newnode;
         else {
            current->next = newnode;
            current = newnode;
         }

         if (*head == NULL) *head = newnode;
      }
   }
   return total;
}

/* Exit procedure, clear the linked list and release the memory allocation */
void exit_proc(struct aminostr *head)
{
   struct aminostr *ptr;

   while (head) {
      ptr = head;
      head = head->next;
      free(ptr);
   }
   exit(0);
}

int deletion(struct aminostr *head, char *arg)
{
   char numstr[10];
   struct aminostr *ptr, *tmp;
   int pos;

   strcpy(numstr, &arg[1]);
   pos = atoi(numstr);

   ptr = head;
   while (ptr) {
      if (ptr->next->position == pos) break;
      ptr = ptr->next;
   }
   tmp = ptr->next;
   ptr->next = tmp->next;
   free(tmp);

   return 0;
}

int mutation(struct aminostr *head, char *arg)
{
   struct aminostr *ptr;
   char mut_from, mut_to;
   char numstr[10];
   int pos;

   mut_from = arg[0];
   mut_to = arg[strlen(arg) - 1];
   strncpy(numstr, &arg[1], strlen(arg) - 2);
   pos = atoi(numstr);

   ptr = head;
   while (ptr) {
      if (ptr->position == pos) break;
      ptr = ptr->next;
   }

   if (ptr && ptr->aminochar == mut_from) {
      ptr->aminochar = mut_to;
   }
   return 0;
}

void write_output(struct aminostr *head, int total, char *variant)
{
   int i, j;
   int done=0, count;
   struct aminostr *ptr;

   printf("Spike protein sequence for %s:\n", variant);
   count = 0;
   ptr = head;
   while (!done) {
      for (i = 1; i <= 5; i++) {
         count += 10;
         if (count <= total) printf("%10d", count);
         else printf("%10s", "");

         if (i < 5) printf(" ");
      }
      printf("\n");

      for (i = 0; i < 5; i++) {
         for (j = 0; j < 10; j++) {
            printf("%c", ptr->aminochar);
            ptr = ptr->next;
            if (!ptr) {
               done = 1;
               break;
            }
         }
         if (!ptr) break;
         if (i < 4) printf(" ");
      }
      printf("\n");

      if (count > total) break;
   }
}


int main(int argc, char *argv[])
{
   int i, total;
   char variant[30];
   struct aminostr *head=NULL;

   total = load_data(&head);

   strcpy(variant, argv[1]);
   for (i = 2; i < argc; i++) {
      if (argv[i][0] == 'd') {
         deletion(head, argv[i]);
         total--;
      } else {
         mutation(head, argv[i]);
      }
   }
   write_output(head, total, variant);
   exit_proc(head);

   return 0;
}
