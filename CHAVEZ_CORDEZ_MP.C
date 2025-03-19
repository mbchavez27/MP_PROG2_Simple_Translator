#include "Headers.h"
#include <stdio.h>
#include <string.h>

void DisplayPairs(EntryTag Entry) {
  int i = 0;

  for (i = 0; i < Entry.nEntryPairs; i++) {
    printf("%s \t%s\n", Entry.EntryPair[i].language,
           Entry.EntryPair[i].translation);
  }
  printf("\n");
}

void DisplayPair(EntryPairTag EntryPair) {
  printf("%s \t%s\n", EntryPair.language, EntryPair.translation);
  printf("\n");
}

void DisplayAllEntries(EntryTag Entry[], int nEntry) {
  int i = 0;

  printf("Language\tTranslation\n");
  if (nEntry > 0) {
    for (i = 0; i < nEntry; i++) {
      printf("%d: ", i + 1);
      DisplayPairs(Entry[i]);
    }
  } else {
    printf("No Entries\n\n");
  }
}

void DeleteEntry(EntryTag Entries[], int *nEntry, int index) {
  int j = 0;

  printf("Deleted Entry #%d\n\n", index);
  index = index - 1;

  for (j = index; j < *nEntry - 1; j++) {
    Entries[j] = Entries[j + 1];
  }
  Entries[j].nEntryPairs--;
  (*nEntry)--;
}

void SearchWord(EntryTag Entries[], int nEntry) {
  String20 word;
  printf("Search word: ");
  scanf("%s", word);
  int i = 0;
  int j = 0;
  printf("\n");

  printf("Language\tTranslation\n");
  for (i = 0; i < nEntry; i++) {
    for (j = 0; j < Entries[i].nEntryPairs; j++) {
      if (strcmp(word, Entries[i].EntryPair[j].translation) == 0) {
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
  int j = 0;

  printf("Language\tTranslation\n");
  if (numOfSameEntry > 1) {
    for (i = 0; i < numOfSameEntry; i++) {
      for (j = 0; j < Entries[EntryPairIndex[i]].nEntryPairs; j++) {
        if (strcmp(language,
                   Entries[EntryPairIndex[i]].EntryPair[j].language) == 0 &&
            strcmp(translation,
                   Entries[EntryPairIndex[i]].EntryPair[j].translation) == 0) {
          DisplayPair(Entries[EntryPairIndex[i]].EntryPair[j]);
        }
      }
    }
  } else {
    for (i = 0; i < Entries[sameEntry].nEntryPairs; i++) {
      if (strcmp(language, Entries[sameEntry].EntryPair[i].language) == 0 &&
          strcmp(translation, Entries[sameEntry].EntryPair[i].translation) ==
              0) {
        DisplayPair(Entries[sameEntry].EntryPair[i]);
      }
    }
  }
}

void AddTranslation(int *nEntry, EntryTag Entries[]) {
  int numOfSameEntries = 0;
  int i = 0;
  String20 language, translation;

  printf("Find Language (STOP! to terminate command): ");
  scanf("%s", language);
  printf("Find Translation (STOP! to terminate command): ");
  scanf("%s", translation);
  printf("\n\n");

  int EntryPairIndex[MAXPAIRS];

  int sameEntry = SearchEntry(Entries, *nEntry, language, translation,
                              EntryPairIndex, &numOfSameEntries);

  if (strcmp(language, "STOP!") != 0 || strcmp(translation, "STOP!") != 0) {
    if (sameEntry != -1) {
      if (numOfSameEntries == 1) {
        DisplayPairs(Entries[sameEntry]);
        printf("Add Language (STOP! to terminate command): ");
        scanf("%s", language);
        printf("Add Translation (STOP! to terminate command): ");
        scanf("%s", translation);
        printf("\n");

        if (strcmp(language, "STOP!") != 0 ||
            strcmp(translation, "STOP!") != 0) {
          strcpy(Entries[sameEntry].EntryPair[Entries->nEntryPairs].language,
                 language);
          strcpy(Entries[sameEntry].EntryPair[Entries->nEntryPairs].translation,
                 translation);
          Entries[sameEntry].nEntryPairs++;
        } else {
          printf("Cancelled Command\n");
        }
      } else {
        int input = -1;

        do {
          for (i = 0; i < numOfSameEntries; i++) {
            printf("Entry #%d:\n", i + 1);
            DisplayPairs(Entries[EntryPairIndex[i]]);
          }
          printf("Pick a Entry to add translations...: ");
          scanf("%d", &input);
        } while (input < 0 || input > numOfSameEntries);

        printf("Chosen Entry #%d\n", input);

        printf("Add Language (STOP! to terminate command): ");
        scanf("%s", language);
        printf("Add Translation (STOP! to terminate command): ");
        scanf("%s", translation);
        printf("\n");

        if (strcmp(language, "STOP!") != 0 ||
            strcmp(translation, "STOP!") != 0) {
          strcpy(Entries[EntryPairIndex[input - 1]]
                     .EntryPair[Entries[EntryPairIndex[input - 1]].nEntryPairs]
                     .language,
                 language);
          strcpy(Entries[EntryPairIndex[input - 1]]
                     .EntryPair[Entries[EntryPairIndex[input - 1]].nEntryPairs]
                     .translation,
                 translation);
          Entries[EntryPairIndex[input - 1]].nEntryPairs++;
        } else {
          printf("Cancelled Command\n");
        }
      }
    } else {
      printf("No Entry Yet... Add Entry an entry first\n\n");
    }
  } else {
    printf("Cancelled Command\n");
  }
}

void AddEntry(EntryTag *Entry, int *nEntry, EntryTag Entries[]) {
  int nEntryPairs = Entry->nEntryPairs;
  int numOfSameEntries = 0;
  String20 language, translation;

  printf("Add Language (STOP! to terminate command): ");
  scanf("%s", language);
  printf("Add Translation (STOP! to terminate command): ");
  scanf("%s", translation);
  printf("\n");

  int EntryPairIndex[MAXPAIRS];
  int sameEntry = SearchEntry(Entries, *nEntry, language, translation,
                              EntryPairIndex, &numOfSameEntries);

  if (strcmp(language, "STOP!") != 0 || strcmp(translation, "STOP!") != 0) {
    if (sameEntry != -1) {
      int input;

      printf("Entry Exists: %s: %s\n", language, translation);

      printf("New Entry?[0/1]: ");
      scanf("%d", &input);
      if (input == 1) {
        strcpy(Entry->EntryPair[nEntryPairs].translation, translation);
        strcpy(Entry->EntryPair[nEntryPairs].language, language);
        Entry->nEntryPairs++;
        (*nEntry)++;
      }
    } else {
      strcpy(Entry->EntryPair[nEntryPairs].translation, translation);
      strcpy(Entry->EntryPair[nEntryPairs].language, language);
      Entry->nEntryPairs++;
      (*nEntry)++;
    }
  } else {
    printf("Cancelled Command\n");
  }
  printf("\n");
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
    printf("\n");

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
        printf("\n");
        if (input == 1) {
          AddEntry(&Entries[nEntry], &nEntry, Entries);
        }
        if (input == 2) {
          AddTranslation(&nEntry, Entries);
        }
        if (input == 3) {
          int index = 0;
          printf("Select Entry Number to Delete:\n");
          DisplayAllEntries(Entries, nEntry);
          printf("Index: ");
          scanf("%d", &index);
          DeleteEntry(Entries, &nEntry, index);
        }
        if (input == 4) {
          int index = 0;
          printf("Select Entry Number:\n");
          DisplayAllEntries(Entries, nEntry);
          printf("Index: ");
          scanf("%d", &index);
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
