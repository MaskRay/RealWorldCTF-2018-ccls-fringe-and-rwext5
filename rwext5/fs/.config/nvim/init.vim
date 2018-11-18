let g:ale_linters = {'c': ['ccls'], 'cpp': ['ccls']}
let g:LanguageClient_serverCommands = { 'c': ['ccls'], 'cpp': ['ccls'], 'cuda': ['ccls'], 'objc': ['ccls'] }
au User lsp_setup call lsp#register_server({
      \ 'name': 'ccls',
      \ 'cmd': {server_info->['ccls']},
      \ 'root_uri': {server_info->lsp#utils#path_to_uri(lsp#utils#find_nearest_parent_file_directory(lsp#utils#get_buffer_path(), '.ccls-root'))},
      \ 'whitelist': ['c', 'cpp', 'objc', 'objcpp', 'cc'],
      \ })

fu! C_init()
  nn <silent><buffer> <C-k> :call LanguageClient#findLocations({'method':'$ccls/navigate','direction':'L'})<cr>
  nn <silent><buffer> <C-l> :call LanguageClient#findLocations({'method':'$ccls/navigate','direction':'D'})<cr>
  nn <silent><buffer> <C-h> :call LanguageClient#findLocations({'method':'$ccls/navigate','direction':'U'})<cr>
  nn <silent><buffer> <C-j> :call LanguageClient#findLocations({'method':'$ccls/navigate','direction':'R'})<cr>
endfu

so ~/.vim/bundle/vim-plug/plug.vim
call plug#begin('~/.vim/bundle')
Plug 'autozimu/LanguageClient-neovim', {'branch': 'next'}
Plug 'neoclide/coc.nvim', {'tag': '*', 'do': { -> coc#util#install()}}
Plug 'prabirshrestha/async.vim'
Plug 'prabirshrestha/vim-lsp'
Plug 'w0rp/ale'
call plug#end()
