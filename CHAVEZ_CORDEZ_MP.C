#include <stdio.h>
#include <string.h>
#include "Headers.h"

void DisplayPairs(EntryTag Entry)
{
  int i = 0;

  for (i = 0; i < Entry.nEntryPairs; i++)
  {
    printf("%s: %s\n", Entry.EntryPair[i].language, Entry.EntryPair[i].translation);
  }
}

void DisplayAllEntries(EntryTag Entry[], int nEntry)
{
  int i = 0;
  int j = 0;

  for (i = 0; i < nEntry; i++)
  {
    int nEntryPairs = Entry[i].nEntryPairs;
    for (j = 0; j < nEntryPairs; j++)
    {
      printf("%d: \n", Entry[i].EntryKey);
      printf("%s: %s\n\n", Entry[i].EntryPair[j].language, Entry[i].EntryPair[j].translation);
    }
  }
  printf("\n\n");
}

int SearchEntryPair(EntryPairTag EntryPair[], int nEntryPairs, String20 language, String20 translation)
{
  int i = 0;
  int SearchEntryIndex = -1;

  for (i = 0; i < nEntryPairs; i++)
  {
    if (strcmp(EntryPair[i].language, language) == 0 && strcmp(EntryPair[i].translation, translation) == 0)
      SearchEntryIndex = i;
  }
  return SearchEntryIndex;
}

int SearchEntry(EntryTag Entries[], int nEntry, String20 language, String20 translation, int *EntryIndex, int *numOfSameEntry)
{
  int i = 0;
  int SearchEntryPairIndex = -1;

  for (i = 0; i < nEntry; i++)
  {
    if (SearchEntryPair(Entries[i].EntryPair, Entries[i].nEntryPairs, language, translation) != -1)
    {
      SearchEntryPairIndex = i;
      (*numOfSameEntry)++;
    }
  }

  return SearchEntryPairIndex;
}

void AddTranslation(EntryTag *Entry, int *nEntry, EntryTag Entries[])
{
  int nEntryPairs = Entry->nEntryPairs;
  int numOfSameEntries = 0;
  String20 language, translation;

  printf("Find Language: ");
  scanf("%s", language);
  printf("Find Translation: ");
  scanf("%s", translation);
  printf("\n\n");

  int EntryPairIndex = 0;

  int sameEntry = SearchEntry(Entries, *nEntry, language, translation, &EntryPairIndex, &numOfSameEntries);

  if (sameEntry != -1)
  {
    if (numOfSameEntries == 1)
    {
      DisplayPairs(Entries[sameEntry]);
      printf("Add Language: ");
      scanf("%s", language);
      printf("Add Translation: ");
      scanf("%s", translation);
      printf("\n\n");
      strcpy(Entries[sameEntry].EntryPair[nEntryPairs].language, language);
      strcpy(Entries[sameEntry].EntryPair[nEntryPairs].translation, translation);
    }
    else
    {
    }
  }
  else
  {
    printf("No Entry Yet... Add Entry an entry first\n\n");
  }
}

void AddEntry(EntryTag *Entry, int *nEntry, EntryTag Entries[])
{
  int nEntryPairs = Entry->nEntryPairs;
  int numOfSameEntries = 0;
  String20 language, translation;

  printf("Add Language: ");
  scanf("%s", language);
  printf("Add Translation: ");
  scanf("%s", translation);
  printf("\n\n");

  int EntryPairIndex = 0;
  int sameEntry = SearchEntry(Entries, *nEntry, language, translation, &EntryPairIndex, &numOfSameEntries);

  if (sameEntry != -1)
  {
    int input;
    printf("Given Entry: %s: %s\n", language, translation);
    printf("Entry Exists: %s: %s\n", Entry[sameEntry].EntryPair[EntryPairIndex].language, Entry[sameEntry].EntryPair[EntryPairIndex].translation);

    printf("New Entry?[0/1]: ");
    scanf("%d", &input);
    if (input == 1)
    {
      strcpy(Entry->EntryPair[nEntryPairs].translation, translation);
      strcpy(Entry->EntryPair[nEntryPairs].language, language);
      Entry->EntryKey = (*nEntry + 1);
      Entry->nEntryPairs++;
      (*nEntry)++;
    }
  }
  else
  {
    strcpy(Entry->EntryPair[nEntryPairs].translation, translation);
    strcpy(Entry->EntryPair[nEntryPairs].language, language);
    Entry->EntryKey = (*nEntry + 1);
    Entry->nEntryPairs++;
    (*nEntry)++;
  }
}

int main()
{
  int input = 0;
  EntryTag Entries[MAXENTRIES] = {0};
  int nEntry = 0;

  while (input != 3)
  {
    printf("Language Translator: \n");
    printf("1. Manage Data\n");
    printf("2. Translate Menu\n");
    printf("3. Exit\n");
    printf("Action: ");
    scanf("%d", &input);
    printf("\n\n");

    // Manage Data
    if (input == 1)
    {
      while (input != 10)
      {
        printf("Manage Data: \n");
        printf("1. Add Entry\n");
        printf("2. Add Translations\n");
        printf("3. Delete Entry\n");
        printf("4. Delete Translations\n");
        printf("5. Display All Entries\n");
        printf("6. Search Word\n");
        printf("7. Search Translations\n");
        printf("8. Export\n");
        printf("9. Import\n");
        printf("10. Exit\n");
        printf("Action: ");
        scanf("%d", &input);
        printf("\n\n");
        if (input == 1)
        {
          AddEntry(&Entries[nEntry], &nEntry, Entries);
        }
        if (input == 2)
        {
          AddTranslation(&Entries[nEntry], &nEntry, Entries);
        }
        if (input == 5)
        {
          DisplayAllEntries(Entries, nEntry);
        }
      }
    }

    // Translate Menu
    if (input == 2)
    {
    }
  }
}