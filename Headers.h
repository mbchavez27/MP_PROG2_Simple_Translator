#define MAXPAIRS 10
#define MAXENTRIES 150

typedef char String20[21];

typedef struct
{
    int EntryPairKey;
    String20 language;
    String20 translation;
} EntryPairTag;

typedef struct
{
    int nEntryPairs;
    int EntryKey;
    EntryPairTag EntryPair[MAXPAIRS];
} EntryTag;

void AddEntry(EntryTag Entry, int *nEntry);