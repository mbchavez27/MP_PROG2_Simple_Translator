#include <stdio.h>
#define MAXLETTERS 20

typedef char String20[21];

#define MAXPAIRS 10
#define MAXENTRY 150

struct EntryPair {
  String20 language;
  String20 translation;
};

struct EntryList {
  EntryPair entries[MAXPAIRS];
};

void AddEntry(struct EntryList *entry) {}

int SearchEntryPair(struct EntryPair *entryPair) {}

int main() {
  int input = 0;

  EntryList Entry[MAXENTRY];

  do {
    printf("Translator:\n");
    printf("1.) Translate Menu \n");
    printf("2.) Manage Data \n");
    printf("3.) Exit \n");
    printf("Choose Option: ");
    scanf("%d", &input);

    if (input == 2) {
      printf("\nGoing to Manage Data\n\n");
      int input = 0;
      do {
        printf("Manage Data:\n");
        printf("1.) Add Entry\n");
        printf("2.) Add Translations\n");
        printf("3.) Delete Entry\n");
        printf("4.) Delete Translation\n");
        printf("5.) Display All Entries\n");
        printf("6.) Search Word\n");
        printf("7.) Search Translation\n");
        printf("8.) Export\n");
        printf("9.) Import\n");
        printf("10.) Exit\n");
        printf("Choose Option: ");
        scanf("%d", &input);

        if (input == 1) {
          printf("Going to Add Entry\n");
          AddEntry(Entry);
        }

        if (input == 10)
          printf("\nGoing Back to Main Menu\n");
      } while (input != 10);
    }
    if (input == 3) {
      printf("\nQuitting the Program\n");
    } else {
      printf("\nInvalid Option\n");
    }
  } while (input != 3);

  return 0;
}
