set history=5000
set ambiwidth=double
set tabstop=4
set shiftwidth=4
set expandtab

set backup
set backupdir=~/.vimtmp
set directory=~/.vimtmp
source $VIMRUNTIME/macros/matchit.vim
if expand("%:e") == 'tpl'
    let b:match_ignorecase = 1
    let b:match_words = '<:>,(:),{:},[:],' .
    \ '<\@<=[ou]l\>[^>]*\%(>\|$\):<\@<=li\>:<\@<=/[ou]l>,' .
    \ '<\@<=dl\>[^>]*\%(>\|$\):<\@<=d[td]\>:<\@<=/dl>,' .
    \ '<\@<=\([^/][^ \t>]*\)[^>]*\%(>\|$\):<\@<=/\1>,' .
    \ '{if.\{-}}:{elseif.\{-}}:{else}:{/if},{foreach.\{-}}:{/foreach},' .
    \ '$Html->scriptStart:$Html->scriptEnd,$CvForm->create:$CvForm->end'
endif

"ステータスラインに文字コードやBOM、16進表示等表示
set laststatus=2
set statusline=%<%f\ %m\ %r%h%w%{'['.(&fenc!=''?&fenc:&enc).(&bomb?':BOM':'').']['.&ff.']'}%=[0x%{FencB()}]\ (%v,%l)/%L%8P\

function! FencB()
  let c = matchstr(getline('.'), '.', col('.') - 1)
  let c = iconv(c, &enc, &fenc)
  return s:Byte2hex(s:Str2byte(c))
endfunction

function! s:Str2byte(str)
  return map(range(len(a:str)), 'char2nr(a:str[v:val])')
endfunction

function! s:Byte2hex(bytes)
  return join(map(copy(a:bytes), 'printf("%02X", v:val)'), '')
endfunction

"set list
set listchars=tab:>-,trail:-,nbsp:%,extends:>,precedes:<

set ignorecase

" バイナリエディタ
map bb :%!xxd<CR>
map bt :%!xxd -r<CR>
