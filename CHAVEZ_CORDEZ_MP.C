#include <stdio.h>
#include <string.h>
#define MAXLETTERS 20

typedef char String20[21];

#define MAXPAIRS 10
#define MAXENTRY 150

struct EntryPair
{
  int EntryPairKey;
  String20 language;
  String20 translation;
};

struct EntryList
{
  int EntryListKey;
  EntryPair entries[MAXPAIRS];
  int nEntryPairs;
};

void DisplayEntries(EntryList *Entry, int nEntry)
{
  int i = 0;
  int j = 0;
  for (i = 0; i < nEntry; i++)
  {
    printf("%d: \n", Entry[i].EntryListKey);
    for (j = 0; j < Entry[i].nEntryPairs; j++)
    {
      printf("%d: %s: %s\n", Entry[i].entries[j].EntryPairKey, Entry[i].entries[j].language, Entry[i].entries[j].translation);
    }
    printf("\n");
  }
  printf("\n");
}

void DisplayTranslations(EntryList *Entry, int nEntry)
{
  int i = 0;
  for (i = 0; i < Entry[nEntry].nEntryPairs; i++)
  {
    printf("%d: %s: %s", Entry[nEntry].nEntryPairs, Entry[nEntry].entries[i].translation, Entry[nEntry].entries[i].language);
    printf("\n");
  }
  printf("\n");
}

int SearchEntryPair(EntryList *Entry, String20 language, String20 translation, int *nEntry)
{
  int isValid = 0;
  int entryNumber = *nEntry;
  if (Entry->nEntryPairs == 0)
  {
    isValid = -1;
  }
  else
  {
    int i = 0;
    int j = 0;
    for (i = 0; i < entryNumber; i++)
    {
      for (j = 0; j < Entry[i].nEntryPairs; j++)
      {
        if (strcmp(language, Entry[i].entries[j].language) == 0 && strcmp(translation, Entry[i].entries[j].translation) == 0)
          isValid = i;
        else
          isValid = -1;
      }
    }
  }
  printf("\n");
  return isValid;
}

void AddEntry(EntryList *Entry, int *nEntry)
{
  String20 language;
  String20 translation;

  EntryList *entry = &Entry[*nEntry];
  int nEntryPairs = entry->nEntryPairs;

  printf("Input Language: ");
  scanf("%s", language);
  printf("Input Translation: ");
  scanf("%s", translation);
  if (SearchEntryPair(Entry, language, translation, nEntry) == -1)
  {
    strcpy(entry->entries[nEntryPairs].language, language);
    strcpy(entry->entries[nEntryPairs].translation, translation);
    entry->entries[nEntryPairs].EntryPairKey = (entry->nEntryPairs + 1);
    entry->EntryListKey = (*nEntry + 1);
    entry->nEntryPairs++;
    (*nEntry)++;
    printf("\n");
  }
  else
  {
    printf("\nENTRY ALREADY EXISTS!\n");
  }
}

void AddTranslation(EntryList *Entry, int *nEntry)
{
  String20 language;
  String20 translation;

  printf("Give a Language and Translation Pair:\n");
  printf("Input Language: ");
  scanf("%s", language);
  printf("Input Translation: ");
  scanf("%s", translation);
  if (SearchEntryPair(Entry, language, translation, nEntry) == -1)
  {
    printf("You need to add entry first before adding translation\n\n");
  }
  else
  {
    int specificTranslation = SearchEntryPair(Entry, language, translation, nEntry);
    DisplayTranslations(Entry, specificTranslation);
    printf("Add a new Language and Translation Pair:\n");
    printf("Input Language: ");
    printf("Input Language: ");
    scanf("%s", language);
    printf("Input Translation: ");
    scanf("%s", translation);
    // strcpy(Entry[])
  }
}

int main()
{
  int input = 0;
  int nEntries = 0;

  EntryList Entry[MAXENTRY] = {0};

  do
  {
    printf("Translator:\n");
    printf("1.) Translate Menu \n");
    printf("2.) Manage Data \n");
    printf("3.) Exit \n");
    printf("Choose Option: ");
    scanf("%d", &input);

    if (input == 2)
    {
      printf("\nGoing to Manage Data\n\n");
      int input = 0;
      do
      {
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

        if (input == 1)
        {
          printf("Going to Add Entry\n");
          AddEntry(Entry, &nEntries);
        }
        else if (input == 2)
        {
          printf("Going to Add Translations\n");
          AddTranslation(Entry, &nEntries);
        }
        else if (input == 5)
        {
          printf("Displaying Entries\n");
          printf("\n");
          DisplayEntries(Entry, nEntries);
        }
        else if (input == 10)
          printf("\nGoing Back to Main Menu\n");
      } while (input != 10);
    }
    if (input == 3)
    {
      printf("\nQuitting the Program\n");
    }
    else
    {
      printf("\nInvalid Option\n");
    }
  } while (input != 3);

  return 0;
}
