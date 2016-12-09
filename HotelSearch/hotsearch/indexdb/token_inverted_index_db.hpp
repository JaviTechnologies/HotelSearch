//
//  invertedindexbd.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/5/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef token_inverted_index_db
#define token_inverted_index_db

#include <set>
#include <map>
#include "hotel.hpp"

using namespace std;

namespace hotsearch
{
    /**
     * InvertedIndexType represents if the word was found in the name, or the address or the description, etc
     */
    enum InvertedIndexType { ANY, NAME, ADRESS, DESCRIPTION };
    
    /**
     * TrieNode is the basic data structure for creating a Trie to store all of our words and retrieve document ids at constant cost.
     * Retrieve a list of ids per word takes O(w), where w is word.length().
     */
    class TrieNode
    {
    public:
        // children of this node
        map<char,TrieNode*> children;
        
        // isCompleteWord flag indicates weather this node contains an entry set
        bool isCompleteWord;
        
        // docIndexLibrary keeps an id list per IndexEntryType
        // TODO: use heap instead of set
        map<hotsearch::LANGUAGE,map<InvertedIndexType,set<long>*>*> docIndexLibrary;
    };
    
    class TokenInvertedIndexDB
    {
        // library: a reference to the root of the trie dictionary
        TrieNode* library;
        
    public:
        // Constructor
        // creates library as the root of the Trie.
        TokenInvertedIndexDB () { library = new TrieNode(); }
        
        // Destructor
        ~TokenInvertedIndexDB() { delete library; }
        
        // void insertWord(string word, long documentId, InvertedIndexType entryType, LANGUAGE lang = LANGUAGE::EN):
        // ---
        // Inserts 'word' into the trie and adds 'documentId' to the indexType list mapped by language lang
        void insertWord(string word, long documentId, InvertedIndexType entryType, LANGUAGE lang);
        
        // void retrieveDocumentsByEntryType(const string &str, set<long> &docIds, InvertedIndexType entryType, LANGUAGE lang = LANGUAGE::EN):
        // ---
        // Retrieves the set of document ids by language and indexType and inserts them into docIds.
        // For example, if EntryType is NAME, then retrieves the set of document ids where str appears in name.
        // Getting the list of documentIds takes O(w) where w is the length of the str.
        void retrieveDocumentsByEntryType(const string &str, set<long> &docIds, InvertedIndexType entryType, LANGUAGE lang);
    };
}

#endif /* token_inverted_index_db */
