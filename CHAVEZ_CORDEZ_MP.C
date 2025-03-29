#include "Headers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/************************************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned.  I have constructed the functions and their respective algorithms and corresponding code by myself.  The
program was run, tested, and debugged by my own efforts.  I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.

                                                                              Charles Stephen C. Cordez, DLSU ID 12411043
                                                                              Max Benedict B. Chavez,    DLSU ID 12328146
************************************************************************************************************************/

/*HELPER
the DisplayPair function prints a single language-translation pair

@param EntryPair - A structure containing the language and translation
*/

void DisplayPair(EntryPairTag EntryPair)
{
  printf("%s: \t%s\n", EntryPair.language, EntryPair.translation);
}

/*HELPER
the DisplayPairs function prints all language-translation pairs in a given entry

@param Entry - A structure containing the language-translation pairs
*/
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

/*HELPER
the RemovePuncMarks function removes punctuation marks (, !, ?, .)

@param word - string containing the word to be removed of puncmarks.
*/

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

/*HELPER
the ReturnPuncMarks checks if the last character of a word
is a punctuation mark (, !, ?, .) and returns it.

@param word - string containing the word to be checked.
*/
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

/*Helper
The SearchEntryPair Function searches for a language-translation pair

@param EntryPair[] - an array of EntryPair structures that contains language-translation pairs
@param nEntryPairs - the number of entry pairs in the array
@param language - the language string to search for
@param translation - the translation string to search for
*/

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

/*HELPER
The SearchEntry Function searches for entries containing a specific language-translation pair

@param Entries[] - an array of EntryTag structures containing entry pairs
@param nEntry - the Total number of entries in the array
@param language - the language string to search for
@param translation - the translation string to search for
@param *EntryIndex - a pointer to an array that stores the indexes of matching entries
@param *numOfSameEntry - a pointer to store the count of matching entries found
*/

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

/*
the DeleteEntry Function removes an entry from the array

@param Entries[] - the array of EntryTag structures
@param *nEntry - Pointer to the number of entries in the array
@param index - the index of the entry to be deleted

*/
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

/* HELPER
The IncludesEnglish Function Checks if Entry Has English Pair

@param Entry - the entry to check for an english language pair

*/

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

/*
The TranslateWord Function

@param word
@param sourceLanguage
@param outputLanguage
@param Entries[]
@param nEntry
@param account

*/

void TranslateWord(String20 word, String20 sourceLanguage,
                   String20 outputLanguage, EntryTag Entries[], int nEntry, String20 account)
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
        for (k = 0; k < Entries[i].nEntryPairs; k++)
        {
          if (strcmp(outputLanguage, Entries[i].EntryPair[k].language) == 0)
          {
            String20 tempWord;
            strcpy(tempWord, word);

            String30 filename = "";
            strcat(filename, account);
            strcat(filename, "WHistory.txt");
            FILE *historyFile = fopen(filename, "a");
            if (historyFile == NULL)
            {
              printf("Error appending word history!\n");
            }

            strcpy(word, Entries[i].EntryPair[k].translation);
            fprintf(historyFile, "%s: %s -> %s: %s\n", sourceLanguage, tempWord, Entries[i].EntryPair[k].language, Entries[i].EntryPair[k].translation);
            fclose(historyFile);
            found = 1;
          }
        }
      }
    }
  }
}

/*
The TranslateText Function

@param sourceText
@param outputText
@param sourceLanguage
@param outputLanguage
@param Entries[]
@param nEntry
@param account

*/

void TranslateText(String150 sourceText, String150 outputText,
                   String20 sourceLanguage, String20 outputLanguage,
                   EntryTag Entries[], int nEntry, String20 account)
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

    TranslateWord(tempWord, sourceLanguage, outputLanguage, Entries, nEntry, account);

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

  if (sourceText[strlen(sourceText) - 1] == '.' ||
      sourceText[strlen(sourceText) - 1] == ',' ||
      sourceText[strlen(sourceText) - 1] == '?' ||
      sourceText[strlen(sourceText) - 1] == '!')
  {
    outputText[strlen(outputText) - 1] = sourceText[strlen(sourceText) - 1];
  }
}

/*
the SplitEntryPair Function

@param line[]
@param words[]

Splits into Translation and Language
*/

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

/*
The SortEntry Function

@param Entries[]
@param nEntry
*/
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

/*
The SortEntryPairs Function

@param *Entry
*/
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

/*
The ModifyEntryPair Function

@param Entries[]
@param index
*/
void ModifyEntryPair(EntryTag Entries[], int index)
{
  int j = 0;
  index = index - 1;
  int indexPair = 0;
  int nCancelled = 0;

  printf("Given Entry Detals\n\n");
  printf("Language\tTranslation\n");
  for (j = 0; j < Entries[index].nEntryPairs; j++)
  {
    printf("%d: ", j + 1);
    DisplayPair(Entries[index].EntryPair[j]);
  }

  printf("\n");

  printf("Choose an Entry Pair Number to Edit: ");
  scanf("%d", &indexPair);
  if (indexPair >= 1 && indexPair <= Entries[index].nEntryPairs)
  {
    String20 language, translation;
    indexPair = indexPair - 1;
    printf("Add Language (STOP! to terminate command): ");
    scanf("%s", language);
    if (strcmp(language, "STOP!") == 0)
    {
      nCancelled = 1;
    }

    if (!nCancelled)
    {
      printf("Add Translation (STOP! to terminate command): ");
      scanf("%s", translation);
      if (strcmp(language, "STOP!") == 0)
      {
        nCancelled = 1;
      }
      printf("\n");
    }

    if (!nCancelled)
    {
      strcpy(Entries[index].EntryPair[indexPair].language, language);
      strcpy(Entries[index].EntryPair[indexPair].translation, translation);
      printf("Entry Pair has been edited!\n");
    }
    else
    {
      printf("Cancelled Command\n");
    }
  }
  else
  {
    printf("Cannot delete entry pair %d\n\n", indexPair);
  }

  printf("\n");
}

/*
The ViewSentenceHistory Function

@param account
*/

void ViewSentenceHistory(String20 account)
{
  String30 filename = "";
  strcat(filename, account);
  strcat(filename, "SHistory.txt");
  FILE *historyFile = fopen(filename, "r");
  char buffer[255];

  if (historyFile == NULL)
  {
    printf("----------------------------------------\n");
    printf("Error reading file\n");
    printf("----------------------------------------\n");
    fclose(historyFile);
  }
  printf("----------------------------------------\n");
  printf("\n");
  printf("Sentence Translation History: \n\n");
  while (fgets(buffer, sizeof(buffer), historyFile) != NULL)
  {
    printf("%s\n", buffer);
  }
  printf("----------------------------------------\n");
  fclose(historyFile);
}

void printTitle(String20 account)
{
  printf("----------------------------------------\n");
  printf("        Language Translator:\n\n");
  printf("Logged in as User: %s\t\n", account);
}

/*
the AddEntry function adds a new language-translation pair to an entry.

@param EntryTag *Entry - Pointer to the entry where the new pair is added.
@param *nEntry - Pointer to the total number of entries in Entries[].
@param Entries[] - The array storing all entries.
*/

void AddEntry(EntryTag *Entry, int *nEntry, EntryTag Entries[])
{
  int nEntryPairs = Entry->nEntryPairs;
  int numOfSameEntries = 0;
  String20 language, translation;
  int nCancelled = 0;

  printf("----------------------------------------------\n");
  printf("Add Language (STOP! to terminate command): ");
  scanf("%s", language);

  if (strcmp(language, "STOP!") == 0)
  {
    nCancelled = 1;
  }

  if (!nCancelled)
  {
    printf("Add Translation (STOP! to terminate command): ");
    scanf("%s", translation);

    if (strcmp(translation, "STOP!") == 0)
    {
      nCancelled = 1;
    }
  }

  if (!nCancelled)
  {
    printf("----------------------------------------------\n");

    int EntryPairIndex[MAXPAIRS];
    int sameEntry = SearchEntry(Entries, *nEntry, language, translation,
                                EntryPairIndex, &numOfSameEntries);

    if (sameEntry != -1)
    {
      char input;
      printf("----------------------------------------------\n");
      printf("Entry Exists:\n");
      printf("Language\tTranslation\n");
      printf("%s \t%s\n\n", language, translation);
      printf("----------------------------------------------\n");

      printf("New Entry? [y/n]: ");
      scanf(" %c", &input);
      printf("\n");
      printf("----------------------------------------------\n");

      if (input == 'y' || input == 'Y')
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

  if (nCancelled)
  {
    printf("----------------------------------------------\n");
    printf("Cancelled Command\n");
    printf("----------------------------------------------\n");
  }
  else
  {
    char input;
    printf("----------------------------------------------\n");
    printf("Add another entry? [y/n]: ");
    scanf(" %c", &input);
    printf("----------------------------------------------\n");

    if (input == 'y' || input == 'Y')
    {
      AddEntry(&Entries[*nEntry], nEntry, Entries);
      printf("\n");
    }
  }
}

/*
the AddTranslation Function adds a new language-pair to an existing entry.
If entry already exists, user can add a translation to it, provided it has not
reached the limit of 10 translations.

@param *nEntry - Pointer to the total number of entries.
@param Entries[] - Array of entries containing language-translation pairs.
*/

void AddTranslation(int *nEntry, EntryTag Entries[])
{
  int numOfSameEntries = 0;
  int i = 0;
  String20 language, translation;
  int nCancelled = 0;

  printf("Find Language (STOP! to terminate command): ");
  scanf("%s", language);

  if (strcmp(language, "STOP!") == 0)
  {
    nCancelled = 1;
  }
  if (!nCancelled)
  {
    printf("Find Translation (STOP! to terminate command): ");
    scanf("%s", translation);
    if (strcmp(translation, "STOP!") == 0)
    {
      nCancelled = 1;
    }
  }

  if (!nCancelled)
  {
    printf("\n\n");
    int EntryPairIndex[MAXPAIRS];
    int sameEntry = SearchEntry(Entries, *nEntry, language, translation,
                                EntryPairIndex, &numOfSameEntries);
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
          if (strcmp(language, "STOP!") == 0)
          {
            nCancelled = 1;
          }

          if (!nCancelled)
          {
            printf("Add Translation (STOP! to terminate command): ");
            scanf("%s", translation);

            if (strcmp(translation, "STOP!") == 0)
            {
              nCancelled = 1;
            }
            printf("\n");
          }

          if (!nCancelled)
          {
            strcpy(Entries[sameEntry].EntryPair[Entries[sameEntry].nEntryPairs].language,
                   language);
            strcpy(
                Entries[sameEntry].EntryPair[Entries[sameEntry].nEntryPairs].translation,
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
          if (strcmp(language, "STOP!") == 0)
          {
            nCancelled = 1;
          }
          if (!nCancelled)
          {
            printf("Add Translation (STOP! to terminate command): ");
            scanf("%s", translation);
            if (strcmp(translation, "STOP!") == 0)
            {
              nCancelled = 1;
            }
            printf("\n");
          }

          if (!nCancelled)
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
  if (nCancelled)
  {
    printf("Cancelled Command\n");
  }
  else
  {
    char input;
    printf("----------------------------------------------\n");
    printf("Add another translation? [y/n]: ");
    scanf(" %c", &input);
    printf("----------------------------------------------\n");
    if (input == 'y' || input == 'Y')
    {
      AddTranslation(nEntry, Entries);
      printf("\n");
    }
  }
}

/*
the DeleteEntryPair Function

@param Entries[]
@param index
*/

void DeleteEntryPair(EntryTag Entries[], int index)
{
  int j = 0;
  index = index - 1;
  int indexPair = 0;
  int k = 0;

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

/*
The DisplayAllEntries Function

@param Entry[]
@param nEntry
*/

void DisplayAllEntries(EntryTag Entry[], int nEntry)
{
  int i = 0;
  char input = '\0';

  SortEntry(Entry, nEntry);

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
        if (i == nEntry - 1)
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

/*
the SearchWord Function

@param Entries[]
@param nEntry

*/

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

/*
the SearchTranslation Functions

@param Entries[]
@param nEntry
*/

void SearchTranslation(EntryTag Entries[], int nEntry)
{
  int i = 0;
  int j = 0;
  int found = 0;
  int EntryPairIndex[MAXPAIRS];
  int numOfSameEntry = 0;
  int nCancelled = 0;

  String20 language, translation;
  printf("Search Language: ");
  scanf("%s", language);
  if (strcmp(language, "STOP!") == 0)
  {
    nCancelled = 1;
  }

  if (!nCancelled)
  {
    printf("Search Translation: ");
    scanf("%s", translation);
    if (strcmp(translation, "STOP!") == 0)
    {
      nCancelled = 1;
    }
    printf("\n\n");
  }

  if (!nCancelled)
  {
    int sameEntry = SearchEntry(Entries, nEntry, language, translation,
                                EntryPairIndex, &numOfSameEntry);

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
        printf("\n");
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
  else
  {
    printf("Cancelled Command\n");
  }
}

/*
the Export Function

@param filename
@param Entries[]
@param nEntry
*/

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

/*
The ImportTranslateText Function

@param sourceFileName
@param outputFileName
@param sourceLanguage
@param outputLanguage
*/

int ImportTranslateText(String20 sourceFileName, String20 outputFileName,
                        String20 sourceLanguage, String20 outputLanguage)
{
  FILE *file = fopen(sourceFileName, "r");
  int success = -1;

  if (file == NULL)
  {
    printf("File: %s does not exist!!!\n", sourceFileName);
    success = -1;
  }
  else
  {
    success = 1;
  }
  return success;
}

/*
The Import Function

@param filename
@param Entries[]
@param *nEntry
*/

int Import(String20 filename, EntryTag Entries[], int *nEntry)
{
  FILE *file = fopen(filename, "r");
  char buffer[255];
  String20 words[2];
  char response;

  int success = 1;
  *nEntry = 0;
  int tempPairs = 0;

  if (file == NULL)
  {
    printf("File: %s does not exist!!!\n", filename);
    success = -1;
  }
  else
  {
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
      if (buffer[0] == '\n' || buffer[0] == '\0')
      {
        if (tempPairs > 0)
        {
          printf("\nEntry #%d:\n", *nEntry + 1);
          printf("Language\tTranslation\n");
          for (int i = 0; i < Entries[*nEntry].nEntryPairs; i++)
          {
            printf("%s: \t%s\n",
                   Entries[*nEntry].EntryPair[i].language,
                   Entries[*nEntry].EntryPair[i].translation);
          }

          printf("\n");
          printf("Confirm adding this entry? (y/n): ");
          scanf(" %c", &response);
          if (response == 'y' || response == 'Y')
          {
            (*nEntry)++;
          }
          else
          {
            Entries[*nEntry].nEntryPairs = 0;
          }
          tempPairs = 0;
        }
      }
      else
      {
        SplitEntryPair(buffer, words);
        if (words[0][0] != '\0' && words[1][0] != '\0' && Entries[*nEntry].nEntryPairs < MAXPAIRS)
        {
          strcpy(Entries[*nEntry].EntryPair[Entries[*nEntry].nEntryPairs].language, words[0]);
          strcpy(Entries[*nEntry].EntryPair[Entries[*nEntry].nEntryPairs].translation, words[1]);
          Entries[*nEntry].nEntryPairs++;
          tempPairs++;
        }
      }
    }

    if (tempPairs > 0)
    {
      printf("\nEntry #%d:\n", *nEntry + 1);
      printf("Language\tTranslation\n");
      for (int i = 0; i < Entries[*nEntry].nEntryPairs; i++)
      {
        printf("%s: \t%s\n",
               Entries[*nEntry].EntryPair[i].language,
               Entries[*nEntry].EntryPair[i].translation);
      }

      printf("\n");
      printf("Confirm adding this entry? (y/n): ");
      scanf(" %c", &response);
      if (response == 'y' || response == 'Y')
      {
        (*nEntry)++;
      }
      else
      {
        Entries[*nEntry].nEntryPairs = 0;
      }
      tempPairs = 0;
    }

    if (*nEntry > 0)
    {
      printf("Translation successfully loaded\n");
    }
    else
    {
      printf("Translation failed\n");
    }
    fclose(file);
  }
  return success;
}

/*
The TranslateTextOption Function *TranslateTextInput, ayusin ko mamaya name

@param Entries[]
@param nEntry
@param account
*/

void TranslateTextInput(EntryTag Entries[], int nEntry, String20 account)
{
  String150 sourceText;
  String150 outputText = "";
  String20 sourceLanguage;
  String20 outputLanguage;
  String30 filename = "";
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
                nEntry, account);

  printf("Translated Text given is: %s\n", outputText);

  strcat(filename, account);
  strcat(filename, "SHistory.txt");
  FILE *historyFile = fopen(filename, "a");
  if (historyFile == NULL)
  {
    printf("Error appending Sentence history!\n");
  }
  fprintf(historyFile, "%s\n", outputText);
  fclose(historyFile);

  printf("\n");
  printf("You can view the previously used translated words and translated sentence in WordsHistory.txt and SentenceHistory.txt\n");
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
    TranslateTextInput(Entries, nEntry, account);
  }
  else
  {
    printf("Going Back to Menu\n");
  }

  printf("\n");
  printf("----------------------------------------\n");
}

/*
the TranslateFile Function  (TranslateTextFile**)

@param sourceFileName
@param outputFileName
@param sourceLanguage
@param outputLanguage
@param Entries[]
@param nEntry
@param account
*/

void TranslateFile(String20 sourceFileName, String20 outputFileName,
                   String20 sourceLanguage, String20 outputLanguage, EntryTag Entries[], int nEntry, String20 account)
{
  FILE *inputFile = fopen(sourceFileName, "r");
  FILE *outputFile = fopen(outputFileName, "w");

  String150 sentence;
  String150 transSentence;
  int index = 0;
  char ch, prevCh = '\0';
  int hasText = 0;

  if (inputFile == NULL)
  {
    printf("File: %s does not exist!!!\n", sourceFileName);
  }
  else
  {
    while ((ch = fgetc(inputFile)) != EOF)
    {
      sentence[index++] = ch;

      if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '.' && ch != '?' && ch != '!')
      {
        hasText = 1;
      }

      if (index == MAXCHARS || (ch == '\n' || ch == '.' || ch == '?' || ch == '!'))
      {

        while ((ch = fgetc(inputFile)) != EOF && (ch == prevCh))
        {
          sentence[index++] = ch;
        }

        if (ch != EOF && ch != prevCh)
        {
          ungetc(ch, inputFile);
        }

        sentence[index] = '\0';
        index = 0;

        if (hasText)
        {
          TranslateText(sentence, transSentence, sourceLanguage, outputLanguage, Entries, nEntry, account);
        }
        else
        {
          strcpy(transSentence, sentence);
        }

        printf("%s\n", transSentence);

        if (
            hasText)
        {
          fprintf(outputFile, "%s\n", transSentence);

          String30 filename = "";
          strcat(filename, account);
          strcat(filename, "SHistory.txt");
          FILE *historyFile = fopen(filename, "a");
          if (historyFile == NULL)
          {
            printf("Error appending history!\n");
          }
          fprintf(historyFile, "%s\n", transSentence);
          fclose(historyFile);
        }

        hasText = 0;
      }
    }
  }

  fclose(inputFile);
  fclose(outputFile);

  printf("\n");
  printf("Translation of file name: %s is done the output can be found at file name: %s", sourceFileName, outputFileName);
  printf("\n");
  printf("You can also view the previously used translated words and translated sentence in WordsHistory.txt and SentenceHistory.txt\n");
}

/*
The ImportFile Function

@param filename
@param Entries[]
@param *nEntry
*/
int ImportFile(String20 filename, EntryTag Entries[], int *nEntry)
{
  FILE *file = fopen(filename, "r");
  char buffer[255];
  String20 words[2];

  int success = 1;

  *nEntry = 0;
  if (file == NULL)
  {
    printf("File: %s does not exist!!!\n", filename);
    success = -1;
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

    if (Entries[*nEntry].nEntryPairs > 0)
    {
      (*nEntry)++;
    }

    printf("Translation successfully loaded\n");
    fclose(file);
  }
  return success;
}

// BONUS FUNCTIONS
void checkWordCount(WordCountTag words[], int *nWords, String20 word)
{
  int i = 0;
  int found = 0;
  for (i = 0; i < *nWords && !found; i++)
  {
    if (strcmp(words[i].word, word) == 0)
    {
      words[i].count++;
      found = 1;
    }
  }
  if (!found)
  {
    strcpy(words[*nWords].word, word);
    words[*nWords].count = 1;
    (*nWords)++;
  }
}

/*BONUS
The ViewWordsHistory Function

@param account

*/

void ViewWordsHistory(String20 account)
{
  String30 filename = "";
  strcat(filename, account);
  strcat(filename, "WHistory.txt");
  FILE *historyFile = fopen(filename, "r");
  char buffer[255];

  if (historyFile == NULL)
  {
    printf("----------------------------------------\n");
    printf("Error reading file\n");
    printf("----------------------------------------\n");
    fclose(historyFile);
  }
  printf("----------------------------------------\n");
  printf("\n");
  printf("Words Translation History: \n\n");
  while (fgets(buffer, sizeof(buffer), historyFile) != NULL)
  {
    printf("%s\n", buffer);
  }
  printf("----------------------------------------\n");
  fclose(historyFile);
}

/*BONUS
The ViewMostTranslatedWord

IN PROGRESS

*/
void ViewMostTranslatedWord(String20 account, WordCountTag words[], int *nWords)
{
  String30 filename = "";
  strcat(filename, account);
  strcat(filename, "WHistory.txt");
  FILE *file = fopen(filename, "r");

  char buffer[255];
  char *token;
  String20 word;

  int maxWord = 0;
  String20 mostTranslatedWord;
  mostTranslatedWord[0] = '\0';
  int i = 0;

  if (file == NULL)
  {
    printf("File: %s does not exist!!!\n", filename);
  }
  else
  {
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
      token = strtok(buffer, ":");

      if (token != NULL)
      {
        token = strtok(NULL, "->");
        if (token != NULL)
        {
          while (*token == ' ')
          {
            token++;
          }

          strcpy(word, token);
          checkWordCount(words, nWords, word);
        }
      }
    }
  }

  fclose(file);

  for (i = 0; i < *nWords; i++)
  {
    if (words[i].count > maxWord)
    {
      maxWord = words[i].count;
      strcpy(mostTranslatedWord, words[i].word);
    }
  }

  printf("Most Translated Word: %s\nTranslated %d times\n\n", mostTranslatedWord, maxWord);
}

/*BONUS
The checkAccount Function

@param account
*/
int checkAccount(String20 account)
{

  FILE *accountFile = fopen("accountsList.txt", "r");
  char buffer[255];
  int found = -1;

  if (accountFile == NULL)
  {
    printf("No Accounts Yet\n\n");
    return -1;
  }
  else
  {
    while (fgets(buffer, sizeof(buffer), accountFile) != NULL)
    {
      char *accountName = strtok(buffer, " \t\n");
      while (accountName != NULL)
      {
        if (strcmp(account, accountName) == 0)
          found = 1;
        accountName = strtok(NULL, " \t\n");
      }
    }
  }

  return found;
}

/*BONUS
the CreateAccount Function

@param account

*/

void CreateAccount(String20 account)
{
  FILE *accountFile = fopen("accountsList.txt", "a");
  if (accountFile == NULL)
  {
    printf("Error appending account!\n");
  }

  fprintf(accountFile, "%s\n", account);

  fclose(accountFile);
}

int main()
{
  int input = 0;
  EntryTag Entries[MAXENTRIES] = {0};
  int nEntry = 0;
  String20 account = "Guest";
  WordCountTag words[MAXWORDS] = {0};
  int nWords = 0;

  while (input != 5)
  {
    printTitle(account);
    printf("----------------------------------------\n");
    printf("1. Manage Data\n");
    printf("2. Translate Menu\n");
    printf("3. View Analytics\n");
    printf("4. Change User\n");
    printf("5. Exit\n");
    printf("----------------------------------------\n");
    printf("Action: ");
    scanf("%d", &input);
    printf("----------------------------------------\n");
    printf("\n");

    // Manage Data
    if (input == 1)
    {
      while (input != 11)
      {
        printTitle(account);
        printf("----------------------------------------\n");
        printf("\t     Manage Data:\t\n");
        printf("----------------------------------------\n");
        printf("1. Add Entry\n");
        printf("2. Add Translations\n");
        printf("3. Modify Entry Pair\n");
        printf("4. Delete Entry\n");
        printf("5. Delete Translations\n");
        printf("6. Display All Entries\n");
        printf("7. Search Word\n");
        printf("8. Search Translations\n");
        printf("9. Export\n");
        printf("10. Import\n");
        printf("11. Exit\n");
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
            printf("Select Entry Number to Edit:\n");
            DisplayAllEntries(Entries, nEntry);
            printf("Entry Index: ");
            scanf("%d", &index);
            if (index >= 1 && index <= (nEntry))
            {
              ModifyEntryPair(Entries, index);
              SortEntry(Entries, nEntry);
            }
            else
            {
              printf("Cant modify given index %d\n\n", index);
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
            printf("Select Entry Number to Delete:\n");
            DisplayAllEntries(Entries, nEntry);
            printf("Entry Index: ");
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
        if (input == 5)
        {
          int index = 0;
          if (nEntry > 0)
          {
            printf("Select Entry Number:\n");
            DisplayAllEntries(Entries, nEntry);
            printf("Entry Index: ");
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
        if (input == 6)
        {
          SortEntry(Entries, nEntry);
          DisplayAllEntries(Entries, nEntry);
        }
        if (input == 7)
        {
          SearchWord(Entries, nEntry);
        }
        if (input == 8)
        {
          SearchTranslation(Entries, nEntry);
          printf("\n");
        }
        if (input == 9)
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
        if (input == 10)
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
          printf("\n");
        }
        if (input == 11)
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
      int translateInput = 0;
      int successImport = -1;
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
        successImport = Import(fileName, Entries, &nEntry);
        if (successImport == -1)
        {
          printf("\n");
        }
        else
        {
          SortEntry(Entries, nEntry);
        }
      }
      while (translateInput != 3 && successImport != -1)
      {
        printf("\n");
        printTitle(account);
        printf("----------------------------------------\n");
        printf("\tTranslate Menu:\t\n");
        printf("----------------------------------------\n");
        printf("1. Translate Text Input\n");
        printf("2. Translate Text File\n");
        printf("3. Exit\n");
        printf("----------------------------------------\n");
        printf("Action: ");
        scanf("%d", &translateInput);
        printf("----------------------------------------\n");

        if (translateInput == 1)
        {
          TranslateTextInput(Entries, nEntry, account);
        }
        if (translateInput == 2)
        {
          String30 sourceFileName, outputFileName;
          String20 sourceLanguage, outputLanguage;
          int successTranslateImport = -1;
          printf("Give Filename to Read: ");
          scanf("%s", sourceFileName);
          printf("Give Language of Source File: ");
          scanf("%s", sourceLanguage);
          printf("Give Filename to Output: ");
          scanf("%s", outputFileName);
          printf("Give Language of Output File: ");
          scanf("%s", outputLanguage);
          printf("\n");

          if (strlen(sourceFileName) > (MAXFILENAMELENGTH - 4))
          {
            printf("Given file name %s exceeds max length!\n", sourceFileName);
          }
          else
          {
            if (strlen(outputFileName) > (MAXFILENAMELENGTH - 4))
            {

              printf("Given file name %s exceeds max length!\n", sourceFileName);
            }
            else
            {
              strcat(sourceFileName, ".txt");
              strcat(outputFileName, ".txt");
              printf("Translating file name: %s to file name: %s\n\n", sourceFileName, outputFileName);
              successTranslateImport = ImportTranslateText(sourceFileName, outputFileName, sourceLanguage, outputFileName);
              if (successTranslateImport != -1)
              {
                TranslateFile(sourceFileName, outputFileName, sourceLanguage, outputLanguage, Entries, nEntry, account);
              }
            }
          }
        }
        if (translateInput == 3)
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

    // View Analytics
    if (input == 3)
    {
      int analyticsInput = 0;
      while (analyticsInput != 4)
      {
        printTitle(account);
        printf("----------------------------------------\n");
        printf("1. View Translated Words History\n");
        printf("2. View Most Translated Word\n");
        printf("3. View Translated Sentences History\n");
        printf("4. Exit\n");
        printf("----------------------------------------\n");
        printf("Action: ");
        scanf("%d", &analyticsInput);
        printf("----------------------------------------\n");
        printf("\n");

        if (analyticsInput == 1)
        {
          ViewWordsHistory(account);
        }
        if (analyticsInput == 2)
        {
          ViewMostTranslatedWord(account, words, &nWords);
        }
        if (analyticsInput == 3)
        {
          ViewSentenceHistory(account);
        }
        else if (analyticsInput == 4)
        {
          printf("----------------------------------------\n");
          printf("Leaving...\n");
          printf("----------------------------------------\n");
        }
      }
    }
    if (input == 4)
    {
      printf("Log In to your Account\n[type Guest if Log in as Guest]: ");
      scanf("%s", account);
      printf("\n");
      int doesExist = checkAccount(account);
      if (doesExist == 1)
      {
        printf("Ok logged in!\n\nHello %s\n\n", account);
      }
      else if (doesExist == -1)
      {
        printf("New Account!\n\nHello %s\n\n", account);
        CreateAccount(account);
      }
    }
  }
}
