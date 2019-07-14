/**
 * Helper function to create =HYPERLINK links for Google Spreadsheets;
 *
 * How to use:
 *
 * (0) Go to a markdown page (e.g., chapter2.md)
 * (1) Open Developer Console on the browser and Copy the code and Paste the output to the spreadsheet
 */
function getTimeComplexity(anchor) {
  try {
    return anchor.parentElement.nextElementSibling.firstElementChild.textContent
      .replace(/time:/i, '')
      .trim();
  } catch {
    return 'NA';
  }
}

function getSpaceComplexity(anchor) {
  try {
    return anchor.parentElement.nextElementSibling.firstElementChild.nextElementSibling.textContent
      .replace(/space:/i, '')
      .trim();
  } catch {
    return 'NA';
  }
}

var anchors = [...document.querySelectorAll('.markdown-body .anchor')].slice(1);
var ret = anchors
  .map(a => {
    let t = getTimeComplexity(a);
    let s = getSpaceComplexity(a);

    return `=HYPERLINK("${a.href}", "${t} / ${s}")`;
  })
  .join('\t');

console.log(ret);
