#include "Headers.h"
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <stdio.h>
#include <string.h>

void RemovePuncMarks(String20 word)
{
  int length = strlen(word);
  while (length > 0 && (word[length - 1] == ',' || word[length - 1] == '!' ||
                        word[length - 1] == '?' || word[length - 1] == '.'))
  {
    word[length - 1] = '\0';
    length--;
  }
}

char ReturnPuncMarks(String20 word)
{
  char puncMark = '\0';
  int length = strlen(word);

  if (word[length - 1] == ',' || word[length - 1] == '!' ||
      word[length - 1] == '?' || word[length - 1] == '.')
  {
    puncMark = word[length - 1];
  }
  return puncMark;
}

// Checks if Entry Has English Pair
int IncludesEnglish(EntryTag Entry)
{
  int i = 0;

  for (i = 0; i < Entry.nEntryPairs; i++)
  {
    if (strcmp(Entry.EntryPair[i].language, "English") == 0)
    {
      return i;
    }
  }
  return -1;
}

// Splits into Translation and Language
void SplitEntryPair(char line[], String20 words[])
{
  int i = 0;
  int character = 0;
  int word = 0;
  while (line[i] != '\0')
  {
    if (line[i] == ' ' || line[i] == '\n')
    {
      if (character > 0)
      {
        words[word][character] = '\0';
        word++;
        character = 0;
      }
    }
    else if (line[i] != ':')
    {
      words[word][character++] = line[i];
    }
    i++;
  }
  if (character > 0)
  {
    words[word][character] = '\0';
  }
}

// Sorts Entry
void SortEntry(EntryTag Entries[], int nEntry)
{
  int i = 0;
  int j = 0;
  int end = nEntry;

  // Puts non English Pairs first at the End
  while (i < end)
  {
    int start = IncludesEnglish(Entries[i]);
    int last = IncludesEnglish((Entries[end]));
    if (start == -1)
    {
      if (last != -1)
      {
        EntryTag temp = Entries[i];
        Entries[i] = Entries[end];
        Entries[end] = temp;
      }
      end--;
    }
    else
    {
      i++;
    }
  }

  // Sorts All Englsh
  for (i = 0; i < end - 1; i++)
  {
    for (j = i + 1; j < end; j++)
    {
      int start = IncludesEnglish(Entries[i]);
      if (start != -1 && end != -1)
      {
        int next = IncludesEnglish((Entries[j]));
        if (strcmp(Entries[i].EntryPair[start].translation,
                   Entries[j].EntryPair[next].translation) > 0)
        {
          EntryTag temp = Entries[i];
          Entries[i] = Entries[j];
          Entries[j] = temp;
        }
      }
    }
  }
}

void SortEntryPairs(EntryTag *Entry)
{
  int i = 0;
  int j = 0;
  int nEntryPairs = Entry->nEntryPairs;

  for (i = 0; i < nEntryPairs - 1; i++)
  {
    int minIndex = i;
    for (j = i + 1; j < nEntryPairs; j++)
    {
      if (strcmp(Entry->EntryPair[j].language,
                 Entry->EntryPair[minIndex].language) < 0)
      {
        minIndex = j;
      }
    }
    EntryPairTag temp = Entry->EntryPair[i];
    Entry->EntryPair[i] = Entry->EntryPair[minIndex];
    Entry->EntryPair[minIndex] = temp;
  }
}

void Export(String20 filename, EntryTag Entries[], int nEntry)
{
  FILE *file;
  file = fopen(filename, "w");
  int i = 0;
  int j = 0;

  for (i = 0; i < nEntry; i++)
  {
    SortEntryPairs(&Entries[i]);
  }

  SortEntry(Entries, nEntry);

  if (file == NULL)
  {
    printf("File: %s does not exist!!!\n", filename);
  }
  else
  {
    for (i = 0; i < nEntry; i++)
    {
      for (j = 0; j < Entries[i].nEntryPairs; j++)
      {
        fprintf(file, "%s: %s\n", Entries[i].EntryPair[j].language,
                Entries[i].EntryPair[j].translation);
      }
      fprintf(file, "\n");
    }
    fclose(file);
    printf("File: %s successfully saved\n", filename);
  }
}

void Import(String20 filename, EntryTag Entries[], int *nEntry)
{
  FILE *file = fopen(filename, "r");
  char buffer[255];
  String20 words[2];

  *nEntry = 0;
  if (file == NULL)
  {
    printf("File: %s does not exist!!!\n", filename);
  }
  else
  {
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
      if (buffer[0] == '\n' || buffer[0] == '\0')
      {
        if (*nEntry < MAXENTRIES)
        {
          (*nEntry)++;
        }
      }
      else
      {
        SplitEntryPair(buffer, words);
        if (Entries[*nEntry].nEntryPairs < MAXPAIRS && words[0][0] != '\0' &&
            words[1][0] != '\0')
        {
          strcpy(
              Entries[*nEntry].EntryPair[Entries[*nEntry].nEntryPairs].language,
              words[0]);
          strcpy(Entries[*nEntry]
                     .EntryPair[Entries[*nEntry].nEntryPairs]
                     .translation,
                 words[1]);
          Entries[*nEntry].nEntryPairs++;
        }
      }
    }
    printf("Translation successfully loaded\n");
    fclose(file);
  }
}

void DisplayPairs(EntryTag Entry)
{
  int i = 0;

  for (i = 0; i < Entry.nEntryPairs; i++)
  {
    printf("%s: \t%s\n", Entry.EntryPair[i].language,
           Entry.EntryPair[i].translation);
  }
  printf("\n");
}

void DisplayPair(EntryPairTag EntryPair)
{
  printf("%s: \t%s\n", EntryPair.language, EntryPair.translation);
}

void DisplayAllEntries(EntryTag Entry[], int nEntry)
{
  int i = 0;
  char input = '\0';

  if (nEntry > 0)
  {
    while (input != 'q' && input != 'Q')
    {
      printf("----------------------------------------\n");
      printf("\n");
      printf("Language\tTranslation\n");
      printf("%d: ", i + 1);
      SortEntryPairs(&Entry[i]);
      DisplayPairs(Entry[i]);
      printf("----------------------------------------\n");
      printf("\n");
      printf("Action (L->Move Left Index, R->Move Right Index,Q->Stop): ");
      scanf(" %c", &input);
      if (input == 'L' || input == 'l')
      {
        if (i == 0)
          printf("Already at the start index!\n");
        else
          i--;
      }
      if (input == 'R' || input == 'r')
      {
        if (i >= nEntry)
          printf("Already at the end index!\n");
        else
          i++;
      }
      if (input == 'Q' || input == 'q')
      {
        printf("Ending display!\n");
      }
      printf("\n");
    }
  }
  else
  {
    printf("No Entries\n\n");
  }
}

void DeleteEntry(EntryTag Entries[], int *nEntry, int index)
{
  int j = 0;

  printf("Deleted Entry #%d\n\n", index);
  index = index - 1;

  for (j = index; j < *nEntry - 1; j++)
  {
    Entries[j] = Entries[j + 1];
  }
  Entries[j].nEntryPairs--;
  (*nEntry)--;
}

void DeleteEntryPair(EntryTag Entries[], int index)
{
  int j = 0;
  index = index - 1;
  if (Entries[index].nEntryPairs > 1)
  {
    printf("Given Entry Detals\n\n");
    printf("Language\tTranslation\n");
    for (j = 0; j < Entries[index].nEntryPairs; j++)
    {
      printf("%d: ", j + 1);
      DisplayPair(Entries[index].EntryPair[j]);
    }

    printf("\n");

    int indexPair = 0;
    int k = 0;
    printf("Choose an Entry Pair Number to Delete: ");
    scanf("%d", &indexPair);
    if (indexPair >= 1 && indexPair <= Entries[index].nEntryPairs)
    {
      indexPair = indexPair - 1;
      for (k = indexPair; k < Entries[index].nEntryPairs - 1; k++)
      {
        Entries[index].EntryPair[k] = Entries[index].EntryPair[k + 1];
      }
      Entries[index].nEntryPairs--;
    }
    else
    {
      printf("Cannot delete entry pair %d\n\n", indexPair);
    }

    printf("\n");
  }
  else
  {
    printf("Given Entry Index #%d has only one entry pair\n\n", index + 1);
  }
}

void SearchWord(EntryTag Entries[], int nEntry)
{
  String20 word;
  printf("Search word: ");
  scanf("%s", word);
  int i = 0;
  int j = 0;
  int found = 0;
  printf("\n");

  printf("----------------------------------------\n");
  printf("\n");
  printf("Language\tTranslation\n");
  for (i = 0; i < nEntry; i++)
  {
    for (j = 0; j < Entries[i].nEntryPairs; j++)
    {
      if (strcmp(word, Entries[i].EntryPair[j].translation) == 0)
      {
        found++;
        DisplayPair(Entries[i].EntryPair[j]);
        printf("\n");
      }
    }
  }
  if (!found)
    printf("No Entries found\n\n");
  printf("----------------------------------------\n");
}

int SearchEntryPair(EntryPairTag EntryPair[], int nEntryPairs,
                    String20 language, String20 translation)
{
  int i = 0;
  int SearchEntryIndex = -1;
  printf("\n");

  for (i = 0; i < nEntryPairs; i++)
  {
    if (strcmp(EntryPair[i].language, language) == 0 &&
        strcmp(EntryPair[i].translation, translation) == 0)
      SearchEntryIndex = i;
  }
  return SearchEntryIndex;
}

int SearchEntry(EntryTag Entries[], int nEntry, String20 language,
                String20 translation, int *EntryIndex, int *numOfSameEntry)
{
  int i = 0;
  int SearchEntryPairIndex = -1;

  for (i = 0; i < nEntry; i++)
  {
    if (SearchEntryPair(Entries[i].EntryPair, Entries[i].nEntryPairs, language,
                        translation) != -1)
    {
      SearchEntryPairIndex = i;
      EntryIndex[*numOfSameEntry] = i;
      (*numOfSameEntry)++;
    }
  }

  return SearchEntryPairIndex;
}

void SearchTranslation(EntryTag Entries[], int nEntry)
{
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
  int found = 0;

  printf("----------------------------------------\n");
  printf("\n");
  printf("Language\tTranslation\n");
  if (numOfSameEntry > 1)
  {
    for (i = 0; i < numOfSameEntry; i++)
    {
      for (j = 0; j < Entries[EntryPairIndex[i]].nEntryPairs; j++)
      {
        if (strcmp(language,
                   Entries[EntryPairIndex[i]].EntryPair[j].language) != 0 &&
            strcmp(translation,
                   Entries[EntryPairIndex[i]].EntryPair[j].translation) != 0)
        {
          found++;
          DisplayPair(Entries[EntryPairIndex[i]].EntryPair[j]);
        }
      }
    }
  }
  else
  {
    for (i = 0; i < Entries[sameEntry].nEntryPairs; i++)
    {
      if (strcmp(language, Entries[sameEntry].EntryPair[i].language) != 0 &&
          strcmp(translation, Entries[sameEntry].EntryPair[i].translation) !=
              0)
      {
        found++;
        DisplayPair(Entries[sameEntry].EntryPair[i]);
      }
    }
  }
  if (!found)
  {
    printf("No Entries found\n\n");
  }
  printf("\n");
  printf("----------------------------------------\n");
}

void AddTranslation(int *nEntry, EntryTag Entries[])
{
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

  if (strcmp(language, "STOP!") != 0 || strcmp(translation, "STOP!") != 0)
  {
    if (sameEntry != -1)
    {
      if (numOfSameEntries == 1)
      {
        if (Entries[sameEntry].nEntryPairs < 10)
        {
          printf("Given Entry Detals\n\n");
          printf("Language\tTranslation\n");
          DisplayPairs(Entries[sameEntry]);
          printf("Add Language (STOP! to terminate command): ");
          scanf("%s", language);
          printf("Add Translation (STOP! to terminate command): ");
          scanf("%s", translation);
          printf("\n");

          if (strcmp(language, "STOP!") != 0 ||
              strcmp(translation, "STOP!") != 0)
          {
            strcpy(Entries[sameEntry].EntryPair[Entries->nEntryPairs].language,
                   language);
            strcpy(
                Entries[sameEntry].EntryPair[Entries->nEntryPairs].translation,
                translation);
            Entries[sameEntry].nEntryPairs++;
          }
          else
          {
            printf("Cancelled Command\n");
          }
        }
        else
        {
          printf("Maximum Number of Translation Pairs Exceeded");
        }
      }
      else
      {
        int input = -1;

        do
        {
          printf("Given Entry Detals\n\n");
          printf("Language\tTranslation\n");
          for (i = 0; i < numOfSameEntries; i++)
          {
            printf("Entry #%d:\n", i + 1);
            DisplayPairs(Entries[EntryPairIndex[i]]);
          }
          printf("Pick a Entry to add translations...: ");
          scanf("%d", &input);
        } while (input < 0 || input > numOfSameEntries);
        if (Entries[EntryPairIndex[input - 1]].nEntryPairs < 10)
        {
          printf("Chosen Entry #%d\n", input);

          printf("Add Language (STOP! to terminate command): ");
          scanf("%s", language);
          printf("Add Translation (STOP! to terminate command): ");
          scanf("%s", translation);
          printf("\n");

          if (strcmp(language, "STOP!") != 0 ||
              strcmp(translation, "STOP!") != 0)
          {
            strcpy(
                Entries[EntryPairIndex[input - 1]]
                    .EntryPair[Entries[EntryPairIndex[input - 1]].nEntryPairs]
                    .language,
                language);
            strcpy(
                Entries[EntryPairIndex[input - 1]]
                    .EntryPair[Entries[EntryPairIndex[input - 1]].nEntryPairs]
                    .translation,
                translation);
            Entries[EntryPairIndex[input - 1]].nEntryPairs++;
          }
          else
          {
            printf("Cancelled Command\n");
          }
        }
        else
        {
          printf(
              "Chosen Entry #%d has already have the max translation pairs\n",
              input);
        }
      }
    }
    else
    {
      printf("No Entry Yet... Add Entry an entry first\n\n");
    }
  }
  else
  {
    printf("Cancelled Command\n");
  }
}

void AddEntry(EntryTag *Entry, int *nEntry, EntryTag Entries[])
{
  int nEntryPairs = Entry->nEntryPairs;
  int numOfSameEntries = 0;
  String20 language, translation;

  printf("----------------------------------------------\n");
  printf("Add Language (STOP! to terminate command): ");
  scanf("%s", language);
  printf("Add Translation (STOP! to terminate command): ");
  scanf("%s", translation);
  printf("----------------------------------------------\n");

  int EntryPairIndex[MAXPAIRS];
  int sameEntry = SearchEntry(Entries, *nEntry, language, translation,
                              EntryPairIndex, &numOfSameEntries);

  if (strcmp(language, "STOP!") != 0 || strcmp(translation, "STOP!") != 0)
  {
    if (sameEntry != -1)
    {
      int input;

      printf("----------------------------------------------\n");
      printf("Entry Exists:\n");
      printf("Language\tTranslation\n");
      printf("%s \t%s\n\n", language, translation);
      printf("----------------------------------------------\n");

      printf("----------------------------------------------\n");
      printf("New Entry?[0/1]: ");
      scanf("%d", &input);
      printf("\n");
      printf("----------------------------------------------\n");
      if (input == 1)
      {
        strcpy(Entry->EntryPair[nEntryPairs].translation, translation);
        strcpy(Entry->EntryPair[nEntryPairs].language, language);
        Entry->nEntryPairs++;
        (*nEntry)++;
      }
    }
    else
    {
      strcpy(Entry->EntryPair[nEntryPairs].translation, translation);
      strcpy(Entry->EntryPair[nEntryPairs].language, language);
      Entry->nEntryPairs++;
      (*nEntry)++;
    }
  }
  else
  {
    printf("----------------------------------------------\n");
    printf("Cancelled Command\n");
    printf("----------------------------------------------\n");
  }

  int input = 0;
  printf("----------------------------------------------\n");
  printf("Add another entry? [0/1]: ");
  scanf("%d", &input);
  printf("----------------------------------------------\n");
  if (input == 1)
  {
    AddEntry(&Entries[*nEntry], nEntry, Entries);
    printf("\n");
  }
  printf("\n");
}

void TranslateWord(String20 word, String20 sourceLanguage,
                   String20 outputLanguage, EntryTag Entries[], int nEntry)
{
  int i = 0;
  int j = 0;
  int k = 0;
  int found = 0;

  for (i = 0; i < nEntry && !found; i++)
  {
    for (j = 0; j < Entries[i].nEntryPairs && !found; j++)
    {
      if (strcmp(word, Entries[i].EntryPair[j].translation) == 0)
      {
        for (k = 0; k < Entries[i].nEntryPairs && !found; k++)
        {
          if (strcmp(outputLanguage, Entries[i].EntryPair[k].language) == 0)
          {
            strcpy(word, Entries[i].EntryPair[k].translation);
            found = 1;
          }
        }
      }
    }
  }
}

void TranslateText(String150 sourceText, String150 outputText,
                   String20 sourceLanguage, String20 outputLanguage,
                   EntryTag Entries[], int nEntry)
{
  String150 tempSource;

  strcpy(tempSource, sourceText);

  outputText[0] = '\0';

  char *token = strtok(tempSource, " ");

  while (token != NULL)
  {

    String20 tempWord;

    char tempChar = ReturnPuncMarks(token) ? ReturnPuncMarks(token) : '\0';

    strcpy(tempWord, token);

    RemovePuncMarks(tempWord);

    TranslateWord(tempWord, sourceLanguage, outputLanguage, Entries, nEntry);

    if (tempChar != '\0')
    {
      char tempStr[2] = {tempChar, '\0'};
      strcat(tempWord, tempStr);
    }

    strcat(outputText, tempWord);

    char *nextToken = strtok(NULL, " ");

    if (nextToken != NULL)
    {
      strcat(outputText, " ");
    }

    token = nextToken;
  }

  if (sourceText[strlen(sourceText) - 1] == '.' || sourceText[strlen(sourceText) - 1] == ',' || sourceText[strlen(sourceText) - 1] == '?' || sourceText[strlen(sourceText) - 1] == '!')
  {
    outputText[strlen(outputText) - 1] = sourceText[strlen(sourceText) - 1];
  }
}

void TranslateTextOption(EntryTag Entries[], int nEntry)
{
  String150 sourceText;
  String150 outputText = "";
  String20 sourceLanguage;
  String20 outputLanguage;
  char input;

  printf("----------------------------------------\n");
  printf("\n");
  printf("Translating Input....\n\n");
  printf("Give Language of Source Text: ");
  scanf("%s", sourceLanguage);
  printf("\n");
  printf("Give Language of Output: ");
  scanf("%s", outputLanguage);

  printf("\n");

  getchar();
  printf("Input the Text: ");
  fgets(sourceText, MAXCHARS, stdin);
  printf("\n");
  printf("Text Given is: %s\n", sourceText);
  sourceText[strlen(sourceText) - 1] = '\0';

  TranslateText(sourceText, outputText, sourceLanguage, outputLanguage, Entries,
                nEntry);

  printf("Translated Text given is: %s\n", outputText);
  printf("----------------------------------------\n");
  printf("\n");

  printf("----------------------------------------\n");
  printf("\n");
  printf("Do you want to input again? [y/n]: ");
  scanf(" %c", &input);
  if (input == 'y')
  {
    printf("Ok!\n");
    printf("\n");
    printf("----------------------------------------\n");

    printf("\n");
    TranslateTextOption(Entries, nEntry);
  }
  else
  {
    printf("Going Back to Menu\n");
  }

  printf("\n");
  printf("----------------------------------------\n");
}

int main()
{
  int input = 0;
  EntryTag Entries[MAXENTRIES] = {0};
  int nEntry = 0;

  while (input != 3)
  {
    printf("----------------------------------------\n");
    printf("\tLanguage Translator:\t\n");
    printf("----------------------------------------\n");
    printf("1. Manage Data\n");
    printf("2. Translate Menu\n");
    printf("3. Exit\n");
    printf("----------------------------------------\n");
    printf("Action: ");
    scanf("%d", &input);
    printf("----------------------------------------\n");
    printf("\n");

    // Manage Data
    if (input == 1)
    {
      while (input != 10)
      {
        printf("----------------------------------------\n");
        printf("\tManage Data:\t\n");
        printf("----------------------------------------\n");
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
        printf("----------------------------------------\n");
        printf("Action: ");
        scanf("%d", &input);
        printf("----------------------------------------\n");
        printf("\n");

        if (input == 1)
        {
          if (nEntry < 150)
          {
            AddEntry(&Entries[nEntry], &nEntry, Entries);
          }
          else
          {
            printf("Already have max number of entries!\n");
          }
          SortEntry(Entries, nEntry);
        }
        if (input == 2)
        {
          AddTranslation(&nEntry, Entries);
          SortEntry(Entries, nEntry);
        }
        if (input == 3)
        {
          int index = 0;
          if (nEntry > 0)
          {
            printf("Select Entry Number to Delete:\n");
            DisplayAllEntries(Entries, nEntry);
            printf("Index: ");
            scanf("%d", &index);
            if (index >= 1 && index <= (nEntry))
            {
              DeleteEntry(Entries, &nEntry, index);
              SortEntry(Entries, nEntry);
            }
            else
            {
              printf("Cant delete given index %d\n\n", index);
            }
          }
          else
          {
            printf("No Entries\n\n");
          }
        }
        if (input == 4)
        {
          int index = 0;
          if (nEntry > 0)
          {
            printf("Select Entry Number:\n");
            DisplayAllEntries(Entries, nEntry);
            printf("Index: ");
            scanf("%d", &index);
            if (index >= 1 && index <= (nEntry))
            {
              DeleteEntryPair(Entries, index);
              SortEntry(Entries, nEntry);
            }
            else
            {
              printf("Cant delete given index %d\n\n", index);
            }
          }
          else
          {
            printf("No Entries\n\n");
          }
        }
        if (input == 5)
        {
          SortEntry(Entries, nEntry);
          DisplayAllEntries(Entries, nEntry);
        }
        if (input == 6)
        {
          SearchWord(Entries, nEntry);
        }
        if (input == 7)
        {
          SearchTranslation(Entries, nEntry);
          printf("\n");
        }
        if (input == 8)
        {
          String30 fileName;
          printf("Give Filename for the Exported Data: ");
          scanf("%s", fileName);
          printf("\n");
          if (strlen(fileName) > (MAXFILENAMELENGTH - 4))
          {
            printf("Given file name %s exceeds max length!\n", fileName);
          }
          else
          {
            strcat(fileName, ".txt");
            printf("Saving data to file name: %s\n\n", fileName);
            Export(fileName, Entries, nEntry);
          }
          printf("\n");
        }
        if (input == 9)
        {
          String30 fileName;
          printf("Give Filename to import Data: ");
          scanf("%s", fileName);
          printf("\n");
          if (strlen(fileName) > (MAXFILENAMELENGTH - 4))
          {
            printf("Given file name %s exceeds max length!\n", fileName);
          }
          else
          {
            strcat(fileName, ".txt");
            printf("Reading data from file name: %s\n\n", fileName);
            Import(fileName, Entries, &nEntry);
          }
          printf("\n");
        }
        if (input == 10)
        {
          printf("----------------------------------------\n");
          printf("Exitting menu!\n");
          printf("----------------------------------------\n");
          printf("\n");
          for (int i = 0; i < MAXENTRIES; i++)
          {
            Entries[i] = (EntryTag){0};
          }
          nEntry = 0;
        }
      }
    }

    // Translate Menu
    if (input == 2)
    {
      String30 fileName;
      printf("Give Filename to import Data: ");
      scanf("%s", fileName);
      printf("\n");
      if (strlen(fileName) > (MAXFILENAMELENGTH - 4))
      {
        printf("Given file name %s exceeds max length!\n", fileName);
      }
      else
      {
        strcat(fileName, ".txt");
        printf("Reading data from file name: %s\n\n", fileName);
        Import(fileName, Entries, &nEntry);
        SortEntry(Entries, nEntry);
      }
      while (input != 3)
      {
        printf("\n");
        printf("----------------------------------------\n");
        printf("\tTranslate Menu:\t\n");
        printf("----------------------------------------\n");
        printf("1. Translate Text Input\n");
        printf("2. Translate Text File\n");
        printf("3. Exit\n");
        printf("----------------------------------------\n");
        printf("Action: ");
        scanf("%d", &input);
        printf("----------------------------------------\n");

        if (input == 1)
        {
          TranslateTextOption(Entries, nEntry);
        }
        if (input == 3)
        {
          printf("----------------------------------------\n");
          printf("Exitting menu!\n");
          printf("----------------------------------------\n");
          printf("\n");
          for (int i = 0; i < MAXENTRIES; i++)
          {
            Entries[i] = (EntryTag){0};
          }
          nEntry = 0;
        }
      }
    }
  }
}
