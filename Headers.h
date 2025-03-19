#define MAXPAIRS 10
#define MAXENTRIES 150

typedef char String20[21];

typedef struct {
  String20 language;
  String20 translation;
} EntryPairTag;

typedef struct {
  int nEntryPairs;
  EntryPairTag EntryPair[MAXPAIRS];
} EntryTag;

void AddEntry(EntryTag Entry, int *nEntry);
