1. Memory managment:
        For memory allocation I use std::unique_ptr mostly. Usually I don't call new or delete manually.
        When one have to use an allocated object - it's okay to pass a raw poiner, because I never call delete manually on any raw pointer.
        So I use a smart pointer for an owner and a raw pointer for an user.
        I don't check for nullptr in methods or constructors because I never pass nullptr into them.

2. Structure:
        GameField -> contains all game data.
        TextureStreamer -> load all texture for render. Renderer is an owner.        
        Renderer -> get GameField's data and render it in a sfml window.
        Input -> get Renderer's sprites and handle player's input.
        AIEnemy -> simulate enemy's moves.

3. AIEnemy:
        I didn't have time to make this class any good :(