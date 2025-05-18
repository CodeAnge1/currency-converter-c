document.addEventListener('DOMContentLoaded', () => {
    const directionSwitcher = document.getElementsByClassName('direction-icon')[0];
    const directionToggle = document.getElementById('direction-toggle');

    directionSwitcher.addEventListener('click', () => {
        directionToggle.checked = !directionToggle.checked;
        //     TODO: add script to change data in input fields
    })

    const currencyPairRedirect = document.getElementById('currency-pair-redirect')
    currencyPairRedirect.addEventListener('click', () => {
        const fromCurrencyName = currencyPairRedirect.dataset.from;
        const toCurrencyName = currencyPairRedirect.dataset.to;
        console.log(fromCurrencyName, toCurrencyName);
        currencyPairRedirect.href = `/currency?c1=${fromCurrencyName}&c2=${toCurrencyName}`;
    });
})