#include <stdio.h>
#include <string.h>
#include "../include/language.h"

// THE global set for language
static char loaded_strings[STRING_COUNT][256];
static const char* NOT_FOUND_MSG = "STR_NOT_FOUND";

/**
 * @brief Loads The language
 * 
 * @param lang_code TR or EN
 * @return int Return'S 1 if successful, otherwise 0.
 */
int loadLanguage(const char* lang_code) {
    char filepath[100];
    
    sprintf(filepath, "data/%s.lang", lang_code);

    FILE* file = fopen(filepath, "r");
    if (file == NULL) {

        
        printf("HATA: Dil dosyasi bulunamadi: %s\n", filepath);
        return 0; 
    }

    char line[256];
    int current_string_id = 0;

    
    while (current_string_id < STRING_COUNT && fgets(line, sizeof(line), file)) {
        
        line[strcspn(line, "\n")] = 0;
        strcpy(loaded_strings[current_string_id], line);
        current_string_id++;
    }

    fclose(file);

    
    if (current_string_id < STRING_COUNT) {
        printf("UYARI: Dil dosyasi eksik! Bazi metinler gorunmeyebilir.\n");
    }

    printf("Dil basariyla yuklendi: %s\n", lang_code);
    return 1; 
}
/**
 * @brief Helper Function that Gets the Strings
 * 
 * @param id the Strings id
 * @return const char* The corresponding string if found, otherwise NOT_FOUND_MSG.
 */
const char* getString(StringID id) {
    if (id >= 0 && id < STRING_COUNT) {
        return loaded_strings[id];
    }



    return NOT_FOUND_MSG;
}