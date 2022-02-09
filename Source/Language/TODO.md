struct languageManager : liste chainée des associations
struct languageBind : "menu_play" associé à "JOUER"

languageManager : 
    2 fonctions : char *getStringById(char *idToGet); // Si on envoie "menu_play" il retourne "JOUER", si il ne trouve pas il renvoie NULL et printf en rouge l'erreur
                  loadLang(char *langId); // langID est un fichier, dans assets/lang (fr_FR.xml, fr_CA.xml, en_US.xml)

languageManager : fonction init, fonction getStringById, fonction loadLang, liste des associations

quand j'init : créer le systeme à partir de en_US
               modifier les associations (pointeur vers le string codé et un pointeur de pointeur vers la traduction)
getStringPtrById renvoie un pointeur de pointeur

Si getStringPtrById ne trouve rien, il renvoie l'id

loadLanguage : load ce qui existe et garde en en_US ce qui n'existe pas
