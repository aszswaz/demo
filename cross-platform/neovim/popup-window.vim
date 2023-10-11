" Define a style called 'PopupDemo'。
:hi PopupDemo guifg='#E06C75' guibg=NONE

:function! PopupDemo()
    let message = 'Hello World'
    for i in range(10)
        let message = message . ' ' . message
    endfor

    let s:win_buf = nvim_create_buf(v:false, v:true)
    call setbufline(s:win_buf, 1, message)
    echo 'buf id: ' . s:win_buf

    let width = 40
    let height = 10
    " Set the new window as the current window.
    let enter = v:false
    " Calculate the centering coordinates.
    let win_x = &columns / 2 - width / 2
    let win_y = &lines / 2 - height / 2

    let s:win_id = nvim_open_win(s:win_buf, enter, {
                \'relative': 'editor',
                \'row': win_y,
                \'col': win_x,
                \'width': width,
                \'height': height,
                \'focusable': v:false,
                \'style': 'minimal',
                \'border': ['╔', '═','╗', '║', '╝', '═', '╚', '║'],
                \'noautocmd': v:false,
                \'bufpos': [0, 0]
                \})

    call nvim_win_set_option(s:win_id, 'wrap', v:true)
    call nvim_win_set_option(s:win_id, 'winhighlight', 'NormalFloat:PopupDemo,FloatBorder:PopupDemo')
    echo 'win id: ' . s:win_id
    call timer_start(5000, 'PopupClose')
:endfunction

:function! PopupClose(timer)
    if s:win_id != 0
        call nvim_win_close(s:win_id, v:false)
    endif
    if s:win_buf != 0
        call nvim_buf_delete(s:win_buf, {'force': v:true})
    endif
:endfunction
