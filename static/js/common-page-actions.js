document.addEventListener('DOMContentLoaded', () => {
    const themeSwitcher = document.getElementById('darkmode-toggle');

    if (localStorage.getItem('dark-theme') === 'true') {
        themeSwitcher.checked = true;
        changeTheme();
    }

    themeSwitcher.addEventListener('click', changeTheme);
});

function changeTheme() {
    const themeSwitcher = document.getElementById('darkmode-toggle');

    themeSwitcher.classList.toggle('light');
    themeSwitcher.classList.toggle('dark');
    document.body.classList.toggle('dark-theme');
    Array.from(document.getElementsByClassName('svg-image')).forEach((elem) => {
        elem.classList.toggle('svg-white');
    });
    localStorage.setItem('dark-theme', String(document.body.classList.contains('dark-theme')))
}
