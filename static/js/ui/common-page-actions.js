document.addEventListener('DOMContentLoaded', () => {
    const themeSwitcher = document.getElementById('darkmode-toggle');

    themeSwitcher.addEventListener('click', () => {
        themeSwitcher.classList.toggle('light');
        themeSwitcher.classList.toggle('dark');
        document.body.classList.toggle('dark-theme');
        Array.from(document.getElementsByClassName('svg-image')).forEach((elem) => {
            elem.classList.toggle('svg-white');
        });
    });
});