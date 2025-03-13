#include "Headers.h"
#include <stdio.h>
#include <string.h>

void DisplayPairs(EntryTag Entry) {
  int i = 0;

  for (i = 0; i < Entry.nEntryPairs; i++) {
    printf("%d: %s: %s\n", Entry.EntryPair[i].EntryPairKey,
           Entry.EntryPair[i].language, Entry.EntryPair[i].translation);
  }
  printf("\n\n");
}

void DisplayPair(EntryPairTag EntryPair) {
  printf("%d: %s: %s\n", EntryPair.EntryPairKey, EntryPair.language,
         EntryPair.translation);
  printf("\n");
}

void DisplayAllEntries(EntryTag Entry[], int nEntry) {
  int i = 0;

  for (i = 0; i < nEntry; i++) {
    printf("%d: \n", Entry[i].EntryKey);
    DisplayPairs(Entry[i]);
  }
  printf("\n\n");
}
void SearchWord(EntryTag Entries[], int nEntry) {
  String20 word;
  printf("Search word: ");
  scanf("%s", word);
  int i = 0;
  int j = 0;

  for (i = 0; i < nEntry; i++) {
    for (j = 0; j < Entries[i].nEntryPairs; j++) {
      if (strcmp(word, Entries[i].EntryPair[j].translation) == 0) {
        printf("%d:\n", Entries[i].EntryKey);
        DisplayPair(Entries[i].EntryPair[j]);
      }
    }
  }
}

int SearchEntryPair(EntryPairTag EntryPair[], int nEntryPairs,
                    String20 language, String20 translation) {
  int i = 0;
  int SearchEntryIndex = -1;

  for (i = 0; i < nEntryPairs; i++) {
    if (strcmp(EntryPair[i].language, language) == 0 &&
        strcmp(EntryPair[i].translation, translation) == 0)
      SearchEntryIndex = i;
  }
  return SearchEntryIndex;
}

int SearchEntry(EntryTag Entries[], int nEntry, String20 language,
                String20 translation, int *EntryIndex, int *numOfSameEntry) {
  int i = 0;
  int SearchEntryPairIndex = -1;

  for (i = 0; i < nEntry; i++) {
    if (SearchEntryPair(Entries[i].EntryPair, Entries[i].nEntryPairs, language,
                        translation) != -1) {
      SearchEntryPairIndex = i;
      EntryIndex[*numOfSameEntry] = i;
      (*numOfSameEntry)++;
    }
  }

  return SearchEntryPairIndex;
}

void SearchTranslation(EntryTag Entries[], int nEntry) {
  String20 language, translation;
  printf("Search Language: ");
  scanf("%s", language);
  printf("Search Translation: ");
  scanf("%s", translation);
  printf("\n\n");
  int EntryPairIndex[MAXPAIRS];
  int numOfSameEntry = 0;

  int sameEntry = SearchEntry(Entries, nEntry, language, translation,
                              EntryPairIndex, &numOfSameEntry);
  int i = 0;
  for (i = 0; i < Entries[sameEntry].nEntryPairs; i++) {
    if (strcmp(language, Entries[sameEntry].EntryPair[i].language) != 0 &&
        strcmp(translation, Entries[sameEntry].EntryPair[i].translation) != 0) {
      DisplayPair(Entries[sameEntry].EntryPair[i]);
    }
  }
}

void AddTranslation(int *nEntry, EntryTag Entries[]) {
  int numOfSameEntries = 0;
  int i = 0;
  String20 language, translation;

  printf("Find Language: ");
  scanf("%s", language);
  printf("Find Translation: ");
  scanf("%s", translation);
  printf("\n\n");

  int EntryPairIndex[MAXPAIRS];

  int sameEntry = SearchEntry(Entries, *nEntry, language, translation,
                              EntryPairIndex, &numOfSameEntries);

  if (sameEntry != -1) {
    if (numOfSameEntries == 1) {
      DisplayPairs(Entries[sameEntry]);
      printf("Add Language: ");
      scanf("%s", language);
      printf("Add Translation: ");
      scanf("%s", translation);
      printf("\n\n");
      strcpy(Entries[sameEntry].EntryPair[Entries->nEntryPairs].language,
             language);
      strcpy(Entries[sameEntry].EntryPair[Entries->nEntryPairs].translation,
             translation);
      Entries[sameEntry].EntryPair[Entries->nEntryPairs].EntryPairKey =
          Entries[sameEntry].nEntryPairs + 1;
      Entries[sameEntry].nEntryPairs++;
    } else {
      int input = -1;
      do {
        for (i = 0; i < numOfSameEntries; i++) {
          printf("Entry #%d:\n", Entries[EntryPairIndex[i]].EntryKey);
          DisplayPairs(Entries[EntryPairIndex[i]]);
        }
        printf("Pick a Entry to add translations...: ");
        scanf("%d", &input);
      } while (input < 0 && input > numOfSameEntries);
      printf("Chosen Entry #%d\n", input);
      printf("Add Language: ");
      scanf("%s", language);
      printf("Add Translation: ");
      scanf("%s", translation);
      printf("\n\n");
      strcpy(Entries[EntryPairIndex[input - 1]]
                 .EntryPair[Entries[EntryPairIndex[input - 1]].nEntryPairs]
                 .language,
             language);
      strcpy(Entries[EntryPairIndex[input - 1]]
                 .EntryPair[Entries[EntryPairIndex[input - 1]].nEntryPairs]
                 .translation,
             translation);
      Entries[EntryPairIndex[input - 1]]
          .EntryPair[Entries[EntryPairIndex[input - 1]].nEntryPairs]
          .EntryPairKey = Entries[EntryPairIndex[input - 1]].nEntryPairs + 1;
      Entries[EntryPairIndex[input - 1]].nEntryPairs++;
    }
  } else {
    printf("No Entry Yet... Add Entry an entry first\n\n");
  }
}

void AddEntry(EntryTag *Entry, int *nEntry, EntryTag Entries[]) {
  int nEntryPairs = Entry->nEntryPairs;
  int numOfSameEntries = 0;
  String20 language, translation;

  printf("Add Language: ");
  scanf("%s", language);
  printf("Add Translation: ");
  scanf("%s", translation);
  printf("\n\n");

  int EntryPairIndex = 0;
  int sameEntry = SearchEntry(Entries, *nEntry, language, translation,
                              &EntryPairIndex, &numOfSameEntries);

  if (sameEntry != -1) {
    int input;
    printf("Given Entry: %s: %s\n", language, translation);
    printf("Entry Exists: %s: %s\n",
           Entry[sameEntry].EntryPair[EntryPairIndex].language,
           Entry[sameEntry].EntryPair[EntryPairIndex].translation);

    printf("New Entry?[0/1]: ");
    scanf("%d", &input);
    if (input == 1) {
      strcpy(Entry->EntryPair[nEntryPairs].translation, translation);
      strcpy(Entry->EntryPair[nEntryPairs].language, language);
      Entry->nEntryPairs++;
      (*nEntry)++;
      Entry->EntryKey = (*nEntry);
      Entry->EntryPair[nEntryPairs].EntryPairKey = Entry->nEntryPairs;
    }
  } else {
    strcpy(Entry->EntryPair[nEntryPairs].translation, translation);
    strcpy(Entry->EntryPair[nEntryPairs].language, language);
    Entry->nEntryPairs++;
    (*nEntry)++;
    Entry->EntryKey = (*nEntry);
    Entry->EntryPair[nEntryPairs].EntryPairKey = Entry->nEntryPairs;
  }
}

int main() {
  int input = 0;
  EntryTag Entries[MAXENTRIES] = {0};
  int nEntry = 0;

  while (input != 3) {
    printf("Language Translator: \n");
    printf("1. Manage Data\n");
    printf("2. Translate Menu\n");
    printf("3. Exit\n");
    printf("Action: ");
    scanf("%d", &input);
    printf("\n\n");

    // Manage Data
    if (input == 1) {
      while (input != 10) {
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
        if (input == 1) {
          AddEntry(&Entries[nEntry], &nEntry, Entries);
        }
        if (input == 2) {
          AddTranslation(&nEntry, Entries);
        }
        if (input == 5) {
          DisplayAllEntries(Entries, nEntry);
        }
        if (input == 6) {
          SearchWord(Entries, nEntry);
        }
        if (input == 7) {
          SearchTranslation(Entries, nEntry);
          printf("\n");
        }
      }
    }

    // Translate Menu
    if (input == 2) {
    }
  }
}
