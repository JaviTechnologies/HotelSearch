//
//  invertedindexbd.cpp
//  HotelSearch
//
//  Created by Javier Campos on 12/5/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#include <map>
#include <set>
#include "token_inverted_index_db.hpp"

using namespace std;

namespace hotsearch
{
//    TokenInvertedIndexDB::~TokenInvertedIndexDB()
//    {
//        delete library;
//    }
    
    // void insertWord(string word, long documentId, InvertedIndexType entryType, LANGUAGE lang = LANGUAGE::EN):
    // ---
    // Inserts 'word' into the trie and adds 'documentId' to the indexType list mapped by language lang
    void TokenInvertedIndexDB::insertWord(string word, long documentId, InvertedIndexType entryType, LANGUAGE lang)
    {
        size_t len = word.length();
        
        TrieNode* currentNode = library;
        char c;
        for (unsigned long i = 0; i < len; i++)
        {
            // get the lower case version
            c = tolower(word[i]);
            
            // add char 'c' as a valid node children if not present
            if (currentNode->children.count(c) == 0)
                currentNode->children.insert(pair<char,TrieNode*>(c,new TrieNode()));
            
            // move pointer
            currentNode = currentNode->children[c];
        }
        
        // check current node for this language
        if (currentNode->docIndexLibrary.count(lang) == 0)
        {
            map<InvertedIndexType,set<long>*>* listMap = new map<InvertedIndexType,set<long>*>();
            currentNode->docIndexLibrary.insert(std::make_pair(lang, listMap));
        }
        
        // check and add currentNode set for this entryType
        if (currentNode->docIndexLibrary[lang]->count(entryType) == 0)
        {
            set<long>* newEntry = new set<long>();
            currentNode->docIndexLibrary[lang]->insert(std::make_pair(entryType,newEntry));
        }
        
        // insert index for this document in a unique list
        (*(currentNode->docIndexLibrary[lang]))[entryType]->insert(documentId);
        
        // mark current node as a complete word
        currentNode->isCompleteWord = true;
    }
    
    // void retrieveDocumentsByEntryType(const string &str, set<long> &docIds, InvertedIndexType entryType, LANGUAGE lang = LANGUAGE::EN):
    // ---
    // Retrieves the set of document ids by language and indexType and inserts them into docIds.
    // For example, if EntryType is NAME, then retrieves the set of document ids where str appears in name.
    // Getting the list of documentIds takes O(w) where w is the length of the str.
    void TokenInvertedIndexDB::retrieveDocumentsByEntryType(const string &str, set<long> &docIds, InvertedIndexType entryType, LANGUAGE lang)
    {
        TrieNode* currentNode = library;
        size_t len = str.length();
        char c;
        for (unsigned long i = 0; i < len; i++)
        {
            // get the lower case version
            c = tolower(str[i]);
            
            // Stop if the char is not found in the children
            // It means the str given is not found in the library.
            // In the future we can retrieve a nearby node, to give suggestions.
            if(currentNode->children.count(c) == 0)
                return;
            
            // move to next node
            currentNode = currentNode->children[c];
        }
        
        // if it is a complete word => check language and documents id lists
        if (currentNode->isCompleteWord &&
            currentNode->docIndexLibrary.count(lang) > 0 &&
            currentNode->docIndexLibrary[lang]->count(entryType) > 0)
        {
            // insert ids into docIds
            set<long>* ids = (*(currentNode->docIndexLibrary[lang]))[entryType];
            docIds.insert(ids->begin(), ids->end());
        }
    }
}
