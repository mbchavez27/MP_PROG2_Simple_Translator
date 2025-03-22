#define MAXPAIRS 10
#define MAXENTRIES 150
#define MAXCHARS 151
#define MAXFILENAMELENGTH 30

typedef char String20[21];
typedef char String30[31];
typedef char String150[151];

typedef struct {
  String20 language;
  String20 translation;
} EntryPairTag;

typedef struct {
  int nEntryPairs;
  EntryPairTag EntryPair[MAXPAIRS];
} EntryTag;

void AddEntry(EntryTag Entry, int *nEntry);
